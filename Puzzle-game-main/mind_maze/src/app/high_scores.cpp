#include "app/high_scores.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "core/json_helpers.h"
#include "core/timer.h"

namespace {

std::string ToUpper(std::string text) {
  for (char& c : text) {
    c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  }
  return text;
}

bool IsBetter(const ScoreEntry& a, const ScoreEntry& b) {
  if (a.solved() != b.solved()) return a.solved() > b.solved();
  return a.total_seconds() < b.total_seconds();
}

std::vector<ScoreEntry> SortedTop10(std::vector<ScoreEntry> list) {
  std::stable_sort(list.begin(), list.end(), IsBetter);
  if (list.size() > 10) list.erase(list.begin() + 10, list.end());
  return list;
}

}

HighScores::HighScores(const std::string& file_path, const GameList& games)
    : file_path_(file_path) {
  for (const auto& game : games) {
    game_keys_.push_back(game->key());
    for (Difficulty difficulty : kAllDifficulties) {
      entries_[ListKey(game->key(), difficulty)];
    }
  }
}

std::string HighScores::ListKey(const std::string& game_key,
                                Difficulty difficulty) {
  return game_key + "/" + DifficultyKey(difficulty);
}

void HighScores::Load() {
  std::ifstream file(file_path_);
  if (!file) return;
  std::stringstream buffer;
  buffer << file.rdbuf();
  const Json text = buffer.str();

  for (const std::string& key : game_keys_) {
    const Json game_json = JsonGetObject(text, key);
    for (Difficulty difficulty : kAllDifficulties) {
      const Json array = JsonGetObject(game_json, DifficultyKey(difficulty));
      std::vector<ScoreEntry>& list = entries_[ListKey(key, difficulty)];
      list.clear();
      std::size_t pos = 0;
      while (true) {
        std::size_t open = array.find('{', pos);
        if (open == std::string::npos) break;
        std::size_t close = array.find('}', open);
        if (close == std::string::npos) break;
        const Json element = array.substr(open, close - open + 1);
        list.push_back(ScoreEntry(JsonGetString(element, "name"),
                                  JsonGetInt(element, "solved"),
                                  JsonGetInt(element, "totalSeconds")));
        pos = close + 1;
      }
    }
  }
}

void HighScores::Save() const {
  std::string text = "{\n";
  for (std::size_t g = 0; g < game_keys_.size(); ++g) {
    text += "  \"" + game_keys_[g] + "\": {\n";
    for (std::size_t d = 0; d < 3; ++d) {
      Difficulty difficulty = kAllDifficulties[d];
      const auto& list = entries_.at(ListKey(game_keys_[g], difficulty));
      text += "    \"" + DifficultyKey(difficulty) + "\": [";
      for (std::size_t i = 0; i < list.size(); ++i) {
        if (i > 0) text += ", ";
        text += "{ \"name\": \"" + list[i].name() +
                "\", \"solved\": " + std::to_string(list[i].solved()) +
                ", \"totalSeconds\": " + std::to_string(list[i].total_seconds()) +
                " }";
      }
      text += (d < 2) ? "],\n" : "]\n";
    }
    text += (g + 1 < game_keys_.size()) ? "  },\n" : "  }\n";
  }
  text += "}\n";

  const std::string temp_path = file_path_ + ".tmp";
  {
    std::ofstream file(temp_path);
    file << text;
  }
  std::filesystem::rename(temp_path, file_path_);
}

void HighScores::RecordSolve(const std::string& game_key, Difficulty difficulty,
                             const std::string& name, int seconds) {
  std::vector<ScoreEntry>& list = entries_[ListKey(game_key, difficulty)];
  for (ScoreEntry& entry : list) {
    if (entry.name() == name) {
      entry.AddSolve(seconds);
      Save();
      return;
    }
  }
  ScoreEntry entry(name, 0, 0);
  entry.AddSolve(seconds);
  list.push_back(entry);
  Save();
}

std::vector<ScoreEntry> HighScores::Top10(const std::string& game_key,
                                          Difficulty difficulty) const {
  return SortedTop10(entries_.at(ListKey(game_key, difficulty)));
}

std::vector<ScoreEntry> HighScores::Overall(const std::string& game_key) const {
  std::vector<ScoreEntry> merged;
  for (Difficulty difficulty : kAllDifficulties) {
    for (const ScoreEntry& entry : entries_.at(ListKey(game_key, difficulty))) {
      bool found = false;
      for (ScoreEntry& total : merged) {
        if (total.name() == entry.name()) {
          total = ScoreEntry(total.name(), total.solved() + entry.solved(),
                             total.total_seconds() + entry.total_seconds());
          found = true;
          break;
        }
      }
      if (!found) merged.push_back(entry);
    }
  }
  return SortedTop10(merged);
}

const ScoreEntry* HighScores::Find(const std::string& game_key,
                                   Difficulty difficulty,
                                   const std::string& name) const {
  for (const ScoreEntry& entry : entries_.at(ListKey(game_key, difficulty))) {
    if (entry.name() == name) return &entry;
  }
  return nullptr;
}

std::string HighScores::FormatAverage(const ScoreEntry& entry) {
  Timer timer;
  timer.set_seconds(static_cast<int>(entry.AverageSeconds() + 0.5));
  return timer.Format();
}

void HighScores::Show(const Game& game, Difficulty difficulty) const {
  PrintTable(ToUpper(game.name()) + " - " + ToUpper(DifficultyName(difficulty)) +
                 " - HIGH SCORES",
             Top10(game.key(), difficulty));
}

void HighScores::ShowOverall(const Game& game) const {
  PrintTable(ToUpper(game.name()) + " - OVERALL - HIGH SCORES",
             Overall(game.key()));
}

void HighScores::PrintTable(const std::string& title,
                            const std::vector<ScoreEntry>& list) const {
  std::cout << "\n=== " << title << " ===\n";
  if (list.empty()) {
    std::cout << "No scores yet.\n";
    return;
  }
  std::cout << std::left << std::setw(4) << "#" << std::setw(12) << "Name"
            << std::setw(8) << "Solved" << "Avg time\n";
  for (std::size_t i = 0; i < list.size(); ++i) {
    std::cout << std::left << std::setw(4) << (std::to_string(i + 1) + ".")
              << std::setw(12) << list[i].name() << std::setw(8)
              << list[i].solved() << FormatAverage(list[i]) << "\n";
  }
}
