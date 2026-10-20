#include "app/save_manager.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#include "core/json_helpers.h"

SaveManager::SaveManager(const std::string& save_dir, const GameList& games)
    : save_dir_(save_dir), games_(games) {}

std::string SaveManager::PathFor(const std::string& name) const {
  return save_dir_ + "/" + name + ".json";
}

bool SaveManager::Exists(const std::string& name) const {
  return std::filesystem::exists(PathFor(name));
}

Player SaveManager::Load(const std::string& name) const {
  Player player(name);
  if (!Exists(name)) return player;  // missing file: a new player

  std::ifstream file(PathFor(name));
  std::stringstream buffer;
  buffer << file.rdbuf();
  const Json text = buffer.str();

  const Json games_json = JsonGetObject(text, "games");
  for (const auto& game : games_) {
    const Json game_json = JsonGetObject(games_json, game->key());
    for (Difficulty difficulty : kAllDifficulties) {
      const Json slot_json = JsonGetObject(game_json, DifficultyKey(difficulty));
      if (!slot_json.empty()) {  // empty means null: no saved Level
        player.SetSlot(game->key(), difficulty,
                       game->LoadLevel(slot_json, difficulty));
      }
    }
  }
  return player;
}

void SaveManager::Save(const Player& player) const {
  std::string text = "{\n  \"name\": \"" + player.name() + "\",\n";
  text += "  \"games\": {\n";
  for (std::size_t g = 0; g < games_.size(); ++g) {
    const std::string& key = games_[g]->key();
    text += "    \"" + key + "\": {\n";
    for (std::size_t d = 0; d < 3; ++d) {
      Difficulty difficulty = kAllDifficulties[d];
      const Level* level = player.Slot(key, difficulty);
      text += "      \"" + DifficultyKey(difficulty) + "\": ";
      text += (level == nullptr) ? "null" : level->ToJson();
      text += (d < 2) ? ",\n" : "\n";
    }
    text += (g + 1 < games_.size()) ? "    },\n" : "    }\n";
  }
  text += "  }\n}\n";

  // Write to a temporary file first, so a crash never leaves a broken save.
  std::filesystem::create_directories(save_dir_);
  const std::string path = PathFor(player.name());
  {
    std::ofstream file(path + ".tmp");
    file << text;
  }
  std::filesystem::rename(path + ".tmp", path);
}
