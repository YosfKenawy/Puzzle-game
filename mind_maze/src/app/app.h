#pragma once

#include <string>

#include "app/high_scores.h"
#include "app/main_menu.h"
#include "app/save_manager.h"
#include "core/game.h"
#include "core/player.h"

// The whole program: asks the name, then runs the menus.
class App {
 public:
  App();
  void Run();

 private:
  std::string AskPlayerName() const;

  // The order matters: games_ must come before the objects that use it.
  GameList games_;
  Player player_;
  SaveManager save_manager_;
  HighScores high_scores_;
  MainMenu main_menu_;
};
