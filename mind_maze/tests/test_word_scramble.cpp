// Plays ONE game alone, without the App, menus or saving to disk.
// To test your own game: copy this file to tests/test_<your_game>.cpp and
// change the two lines marked CHANGE.
#include <iostream>
#include <memory>

#include "core/game.h"
#include "core/input_validator.h"
#include "core/player.h"
#include "games/word_scramble/word_scramble.h"  // CHANGE 1: your game header

namespace {

Difficulty AskDifficulty() {
  std::cout << "1. Easy  2. Medium  3. Hard\n";
  int choice = InputValidator::ReadMenuChoice(1, 3);
  if (choice == 1) return Difficulty::kEasy;
  if (choice == 2) return Difficulty::kMedium;
  return Difficulty::kHard;
}

}  // namespace

int main() {
  std::unique_ptr<Game> game = std::make_unique<WordScramble>();  // CHANGE 2
  Player player("tester");
  Difficulty difficulty = AskDifficulty();

  while (true) {
    PlayResult result = game->Play(difficulty, player);

    if (result.outcome == LevelOutcome::kSavedAndQuit) {
      std::cout << "Saved (" << result.seconds << "s). 1. Continue  2. Exit\n";
      if (InputValidator::ReadMenuChoice(1, 2) == 2) break;
      continue;  // Play() resumes the saved Level
    }

    std::cout << (result.outcome == LevelOutcome::kSolved ? "Result: solved"
                                                          : "Result: failed")
              << " in " << result.seconds << "s\n";

    int choice = game->PlayAgainMenu();
    if (choice == 2) difficulty = AskDifficulty();
    if (choice == 3) break;
  }
  return 0;
}
