#include "games/memory_cards/memory_cards_level.h"

#include <iostream>

#include "core/json_helpers.h"

MemoryCardsLevel::MemoryCardsLevel(Difficulty difficulty)
    : Level(difficulty, kMemoryCardsAttempts) {
}

void MemoryCardsLevel::UseHint() {
  if (hints_left_ <= 0) return;
  --hints_left_;
}

void MemoryCardsLevel::Reset() {
  RefillCounters();
}

void MemoryCardsLevel::Display() const {
  std::cout << "\nDifficulty - " << DifficultyName(difficulty_)
            << "     time: " << timer_.Format() << "\n";
  std::cout << "Hints left: " << hints_left_ << "/"
            << HintsForDifficulty(difficulty_) << "\n";
  std::cout << "Attempts: " << (max_attempts_ - attempts_left_) << "/"
            << max_attempts_ << "\n";
  std::cout << "\nR=Reset H=Hint  I=Rules  S=Save & Quit\n";
}

bool MemoryCardsLevel::IsSolved() const {
  return false;
}

bool MemoryCardsLevel::IsOutOfAttempts() const { return attempts_left_ <= 0; }

Json MemoryCardsLevel::ToJson() const {
  return "{\"hintsLeft\":" + std::to_string(hints_left_) +
         ",\"attemptsLeft\":" + std::to_string(attempts_left_) +
         ",\"seconds\":" + std::to_string(timer_.seconds()) + "}";
}

void MemoryCardsLevel::FromJson(const Json& json) {
  hints_left_ = JsonGetInt(json, "hintsLeft");
  attempts_left_ = JsonGetInt(json, "attemptsLeft");
  timer_.set_seconds(JsonGetInt(json, "seconds"));
}
