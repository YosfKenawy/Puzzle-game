#pragma once

#include <map>
#include <string>
#include <vector>

#include "core/game.h"
#include "core/score_entry.h"
#include "core/types.h"

class HighScores {
 public:
  HighScores(const std::string& file_path, const GameList& games);

  void Load();
  void Save() const;

  void RecordSolve(const std::string& game_key, Difficulty difficulty,
                   const std::string& name, int seconds);

  std::vector<ScoreEntry> Top10(const std::string& game_key,
                                Difficulty difficulty) const;
  std::vector<ScoreEntry> Overall(const std::string& game_key) const;

  const ScoreEntry* Find(const std::string& game_key, Difficulty difficulty,
                         const std::string& name) const;

  void Show(const Game& game, Difficulty difficulty) const;
  void ShowOverall(const Game& game) const;

  static std::string FormatAverage(const ScoreEntry& entry);

 private:
  static std::string ListKey(const std::string& game_key, Difficulty difficulty);
  void PrintTable(const std::string& title,
                  const std::vector<ScoreEntry>& list) const;

  std::string file_path_;
  std::vector<std::string> game_keys_;
  std::map<std::string, std::vector<ScoreEntry>> entries_;
};
