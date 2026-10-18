#include "app/main_menu.h"

#include <iomanip>
#include <iostream>

#include "core/input_validator.h"

MainMenu::MainMenu(const GameList& games) : games_(games) {}

std::string MainMenu::StatusOf(const Game& game, const Player& player) const {
  return player.HasSavedLevel(game.key()) ? "[In progress]" : "[New]";
}

int MainMenu::Show(const Player& player) const {
  std::cout << "\n=== MIND MAZE ===\n";
  for (std::size_t i = 0; i < games_.size(); ++i) {
    std::cout << (i + 1) << ". " << std::left << std::setw(18)
              << games_[i]->name() << StatusOf(*games_[i], player) << "\n";
  }
  std::cout << "0. Exit\n";
  return InputValidator::ReadMenuChoice(0, static_cast<int>(games_.size()));
}
