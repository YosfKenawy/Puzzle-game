#pragma once

#include <string>

#include "core/game.h"

class Wordle : public Game {
 public:
  Wordle();

  int Attempts() const override;
  std::string HowToPlay() const override;
  LevelPtr CreateLevel(Difficulty difficulty) const override;
  LevelPtr LoadLevel(const Json& json, Difficulty difficulty) const override;
  PlayResult Play(Difficulty difficulty, Player& player) override;
};
