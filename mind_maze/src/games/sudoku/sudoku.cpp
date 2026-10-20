#include "games/sudoku/sudoku.h"

#include <iostream>
#include <memory>

#include "games/sudoku/sudoku_level.h"

Sudoku::Sudoku() : Game("sudoku", "Sudoku") {}

int Sudoku::Attempts() const { return kSudokuAttempts; }

std::string Sudoku::HowToPlay() const {
  return "TODO(friend): write one line that explains your game.";
}

LevelPtr Sudoku::CreateLevel(Difficulty difficulty) const {
  return std::make_unique<SudokuLevel>(difficulty);
}

LevelPtr Sudoku::LoadLevel(const Json& json, Difficulty difficulty) const {
  auto level = std::make_unique<SudokuLevel>(difficulty);
  level->FromJson(json);
  return level;
}

PlayResult Sudoku::Play(Difficulty /*difficulty*/, Player& /*player*/) {
  // TODO(friend): replace this with the Level loop. Copy the steps from
  // WordScramble::Play (src/games/word_scramble/word_scramble.cpp).
  std::cout << "\nSudoku is not implemented yet.\n";
  return {LevelOutcome::kSavedAndQuit, 0};
}
