#include "core/game.h"

#include <iostream>

#include "core/input_validator.h"

Game::Game(const std::string& key, const std::string& name)
    : key_(key), name_(name) {}

void Game::ShowRules() const {
  std::cout << "\n=== " << name_ << " - RULES & SCORING ===\n";
  std::cout << "How to play: " << HowToPlay() << "\n";
  std::cout << "Attempts Allowed: " << Attempts() << "\n";
  std::cout << "Hints per Difficulty: " << HintsForDifficulty(Difficulty::kEasy)
            << " (easy) / " << HintsForDifficulty(Difficulty::kMedium)
            << " (medium) / " << HintsForDifficulty(Difficulty::kHard)
            << " (hard)\n";
  std::cout << "Ranking: most Levels solved, then lowest average time.\n\n";
}

int Game::PlayAgainMenu() const {
  std::cout << "\n1. Play again (same difficulty)\n"
            << "2. Change difficulty\n"
            << "3. Back to game menu\n";
  return InputValidator::ReadMenuChoice(1, 3);
}
