#include "games/crosswords/crosswords.h"

#include <iostream>
#include <memory>

#include "games/crosswords/crosswords_level.h"

Crosswords::Crosswords() : Game("crosswords", "Crosswords") {}

int Crosswords::Attempts() const { return kCrosswordsAttempts; }

std::string Crosswords::HowToPlay() const {
  return "TODO(friend): write one line that explains your game.";
}

LevelPtr Crosswords::CreateLevel(Difficulty difficulty) const {
  return std::make_unique<CrosswordsLevel>(difficulty);
}

LevelPtr Crosswords::LoadLevel(const Json& json, Difficulty difficulty) const {
  auto level = std::make_unique<CrosswordsLevel>(difficulty);
  level->FromJson(json);
  return level;
}

PlayResult Crosswords::Play(Difficulty, Player&) {
  std::cout << "\nCrosswords is not implemented yet.\n";
  return {LevelOutcome::kSavedAndQuit, 0};
}
