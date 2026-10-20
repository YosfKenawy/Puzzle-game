#pragma once

#include <string>

#include "core/game.h"
#include "core/player.h"

class MainMenu {
 public:
  explicit MainMenu(const GameList& games);

  int Show(const Player& player) const;

 private:
  std::string StatusOf(const Game& game, const Player& player) const;

  const GameList& games_;
};
