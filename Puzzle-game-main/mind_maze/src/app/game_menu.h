#pragma once

#include "app/high_scores.h"
#include "core/game.h"
#include "core/player.h"

class GameMenu {
 public:
  GameMenu(Game& game, HighScores& high_scores);

  void Show(Player& player);

 private:
  void PlayDifficulty(Player& player, Difficulty difficulty);
  void ShowHighScores() const;
  int AskContinueOrNew() const;
  Difficulty AskDifficulty() const;

  Game& game_;
  HighScores& high_scores_;
};
