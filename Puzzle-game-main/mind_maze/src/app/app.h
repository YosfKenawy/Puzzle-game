#pragma once

#include <string>

#include "app/high_scores.h"
#include "app/main_menu.h"
#include "app/save_manager.h"
#include "core/game.h"
#include "core/player.h"

class App {
 public:
  App();
  void Run();

 private:
  std::string AskPlayerName() const;

  GameList games_;
  Player player_;
  SaveManager save_manager_;
  HighScores high_scores_;
  MainMenu main_menu_;
};
