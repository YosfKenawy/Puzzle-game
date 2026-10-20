#include "games/word_scramble/word_scramble.h"

#include <iostream>
#include <memory>

#include "core/input_validator.h"
#include "core/player.h"
#include "games/word_scramble/word_scramble_level.h"

WordScramble::WordScramble() : Game("wordscramble", "Word Scramble") {}

int WordScramble::Attempts() const { return kWordScrambleAttempts; }

std::string WordScramble::HowToPlay() const {
  return "unscramble the letters to form a word.";
}

LevelPtr WordScramble::CreateLevel(Difficulty difficulty) const {
  return std::make_unique<WordScrambleLevel>(difficulty);
}

LevelPtr WordScramble::LoadLevel(const Json& json, Difficulty difficulty) const {
  auto level = std::make_unique<WordScrambleLevel>(difficulty);
  level->FromJson(json);
  return level;
}

PlayResult WordScramble::Play(Difficulty difficulty, Player& player) {
  Level* level = player.Slot(key_, difficulty);
  if (level == nullptr) {
    player.SetSlot(key_, difficulty, CreateLevel(difficulty));
    level = player.Slot(key_, difficulty);
  }
  auto* word_level = dynamic_cast<WordScrambleLevel*>(level);

  level->timer().Start();
  player.AutoSave();

  while (true) {
    level->Display();

    std::string text;
    InputResult input = InputValidator::ReadLevelInput(&text);

    if (input == InputResult::kInvalid) {
      std::cout << "Invalid input, try again.\n";
      continue;
    }

    if (input == InputResult::kRules) {
      ShowRules();
      continue;
    }

    if (input == InputResult::kSaveQuit) {
      level->timer().Stop();
      player.AutoSave();
      return {LevelOutcome::kSavedAndQuit, level->timer().seconds()};
    }

    if (input == InputResult::kReset) {
      level->Reset();
    } else if (input == InputResult::kHint) {
      if (level->hints_left() == 0) {
        std::cout << "No hints left.\n";
        continue;
      }
      level->UseHint();
    } else {
      word_level->Guess(text);
    }

    if (level->IsSolved()) {
      level->timer().Stop();
      int seconds = level->timer().seconds();
      std::cout << "\nSolved! Time: " << level->timer().Format() << "\n";
      player.ClearSlot(key_, difficulty);
      return {LevelOutcome::kSolved, seconds};
    }

    if (level->IsOutOfAttempts()) {
      level->timer().Stop();
      int seconds = level->timer().seconds();
      std::cout << "\nOut of attempts! The word was: " << word_level->word()
                << "\n";
      player.ClearSlot(key_, difficulty);
      return {LevelOutcome::kFailed, seconds};
    }

    player.AutoSave();
  }
}
