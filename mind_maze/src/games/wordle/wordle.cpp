#include "games/wordle/wordle.h"

#include <iostream>
#include <memory>

#include "games/wordle/wordle_level.h"

Wordle::Wordle() : Game("wordle", "Wordle") {}

int Wordle::Attempts() const { return kWordleAttempts; }

std::string Wordle::HowToPlay() const {
  return "TODO(friend): write one line that explains your game.";
}

LevelPtr Wordle::CreateLevel(Difficulty difficulty) const {
  return std::make_unique<WordleLevel>(difficulty);
}

LevelPtr Wordle::LoadLevel(const Json& json, Difficulty difficulty) const {
  auto level = std::make_unique<WordleLevel>(difficulty);
  level->FromJson(json);
  return level;
}

PlayResult Wordle::Play(Difficulty /*difficulty*/, Player& /*player*/) {
  // TODO(friend): replace this with the Level loop. Copy the steps from
  // WordScramble::Play (src/games/word_scramble/word_scramble.cpp).
  std::cout << "\nWordle is not implemented yet.\n";
  return {LevelOutcome::kSavedAndQuit, 0};
}
