#pragma once

#include "app/high_scores.h"
#include "core/game.h"
#include "core/player.h"

// The menu of one game: difficulties, high scores, rules.
class GameMenu {
 public:
  GameMenu(Game& game, HighScores& high_scores);

  // Runs the menu until the player chooses Back.
  void Show(Player& player);

 private:
  void PlayDifficulty(Player& player, Difficulty difficulty);
  void ShowHighScores() const;
  int AskContinueOrNew() const;  // 1 = continue, 2 = start new, 3 = back
  Difficulty AskDifficulty() const;

  Game& game_;
  HighScores& high_scores_;
};
