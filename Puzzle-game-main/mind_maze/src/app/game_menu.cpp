#include "app/game_menu.h"

#include <cctype>
#include <iomanip>
#include <iostream>

#include "core/input_validator.h"
#include "core/timer.h"

namespace {

std::string ToUpper(std::string text) {
  for (char& c : text) {
    c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  }
  return text;
}

}

GameMenu::GameMenu(Game& game, HighScores& high_scores)
    : game_(game), high_scores_(high_scores) {}

void GameMenu::Show(Player& player) {
  while (true) {
    std::cout << "\n=== " << ToUpper(game_.name()) << " ===\n";
    for (std::size_t i = 0; i < 3; ++i) {
      Difficulty difficulty = kAllDifficulties[i];
      std::cout << (i + 1) << ". " << DifficultyName(difficulty) << " Level";
      if (player.Slot(game_.key(), difficulty) != nullptr) {
        std::cout << "   [In progress]";
      }
      std::cout << "\n";
    }
    std::cout << "4. High Scores\n5. Rules & Scoring\n6. Back\n";

    int choice = InputValidator::ReadMenuChoice(1, 6);
    if (choice >= 1 && choice <= 3) {
      PlayDifficulty(player, kAllDifficulties[choice - 1]);
    } else if (choice == 4) {
      ShowHighScores();
    } else if (choice == 5) {
      game_.ShowRules();
    } else {
      return;
    }
  }
}

void GameMenu::PlayDifficulty(Player& player, Difficulty difficulty) {
  while (true) {
    if (player.Slot(game_.key(), difficulty) != nullptr) {
      std::cout << "\nYou have a saved Level (" << DifficultyName(difficulty)
                << ").\n";
      int choice = AskContinueOrNew();
      if (choice == 3) return;
      if (choice == 2) {
        player.ClearSlot(game_.key(), difficulty);
        player.AutoSave();
      }
    }

    PlayResult result = game_.Play(difficulty, player);
    player.AutoSave();
    if (result.outcome == LevelOutcome::kSavedAndQuit) return;

    if (result.outcome == LevelOutcome::kSolved) {
      high_scores_.RecordSolve(game_.key(), difficulty, player.name(),
                               result.seconds);
      const ScoreEntry* entry =
          high_scores_.Find(game_.key(), difficulty, player.name());
      if (entry != nullptr) {
        std::cout << "Levels solved (" << DifficultyName(difficulty)
                  << "): " << entry->solved()
                  << "   Average time: " << HighScores::FormatAverage(*entry)
                  << "\n";
      }
    }

    int choice = game_.PlayAgainMenu();
    if (choice == 3) return;
    if (choice == 2) difficulty = AskDifficulty();
  }
}

void GameMenu::ShowHighScores() const {
  while (true) {
    std::cout << "\n=== " << ToUpper(game_.name()) << " - HIGH SCORES ===\n"
              << "1. Easy\n2. Medium\n3. Hard\n4. Overall\n5. Back\n";
    int choice = InputValidator::ReadMenuChoice(1, 5);
    if (choice >= 1 && choice <= 3) {
      high_scores_.Show(game_, kAllDifficulties[choice - 1]);
    } else if (choice == 4) {
      high_scores_.ShowOverall(game_);
    } else {
      return;
    }
  }
}

int GameMenu::AskContinueOrNew() const {
  std::cout << "1. Continue\n2. Start new (erases the saved Level)\n3. Back\n";
  return InputValidator::ReadMenuChoice(1, 3);
}

Difficulty GameMenu::AskDifficulty() const {
  std::cout << "\n1. Easy\n2. Medium\n3. Hard\n";
  return kAllDifficulties[InputValidator::ReadMenuChoice(1, 3) - 1];
}
