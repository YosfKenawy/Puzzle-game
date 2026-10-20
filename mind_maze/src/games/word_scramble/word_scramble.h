#pragma once

#include <string>

#include "core/game.h"

// EXAMPLE game. Copy this pattern for your own game.
class WordScramble : public Game {
 public:
  WordScramble();

  int Attempts() const override;
  std::string HowToPlay() const override;
  LevelPtr CreateLevel(Difficulty difficulty) const override;
  LevelPtr LoadLevel(const Json& json, Difficulty difficulty) const override;
  PlayResult Play(Difficulty difficulty, Player& player) override;
};
