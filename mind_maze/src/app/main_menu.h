#pragma once

#include <string>

#include "core/game.h"
#include "core/player.h"

// The first menu: the list of games, plus Exit.
class MainMenu {
 public:
  explicit MainMenu(const GameList& games);

  // Shows the menu and returns 0 for Exit, or the game number (1, 2, 3...).
  int Show(const Player& player) const;

 private:
  std::string StatusOf(const Game& game, const Player& player) const;

  const GameList& games_;
};
