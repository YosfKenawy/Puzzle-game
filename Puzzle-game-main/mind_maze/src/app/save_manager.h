#pragma once

#include <string>

#include "core/game.h"
#include "core/player.h"

class SaveManager {
 public:
  SaveManager(const std::string& save_dir, const GameList& games);

  bool Exists(const std::string& name) const;
  Player Load(const std::string& name) const;
  void Save(const Player& player) const;

 private:
  std::string PathFor(const std::string& name) const;

  std::string save_dir_;
  const GameList& games_;
};
