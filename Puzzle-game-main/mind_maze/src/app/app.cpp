#include "app/app.h"

#include <iostream>

#include "app/game_list.h"
#include "app/game_menu.h"
#include "core/input_validator.h"

App::App()
    : games_(CreateAllGames()),
      save_manager_("saves", games_),
      high_scores_("highscores.json", games_),
      main_menu_(games_) {}

std::string App::AskPlayerName() const { return InputValidator::ReadName(); }

void App::Run() {
  std::string name = AskPlayerName();
  bool is_new_player = !save_manager_.Exists(name);

  player_ = save_manager_.Load(name);
  player_.set_auto_save([this]() { save_manager_.Save(player_); });
  high_scores_.Load();
  player_.AutoSave();

  std::cout << (is_new_player ? "Welcome, " : "Welcome back, ") << name
            << "!\n";

  while (true) {
    int choice = main_menu_.Show(player_);
    if (choice == 0) break;
    GameMenu game_menu(*games_[choice - 1], high_scores_);
    game_menu.Show(player_);
  }

  player_.AutoSave();
  std::cout << "Goodbye!\n";
}
