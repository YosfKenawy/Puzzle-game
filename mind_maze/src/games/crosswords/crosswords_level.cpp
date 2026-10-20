#include "games/crosswords/crosswords_level.h"

#include <iostream>

#include "core/json_helpers.h"

CrosswordsLevel::CrosswordsLevel(Difficulty difficulty)
    : Level(difficulty, kCrosswordsAttempts) {
  // TODO(friend): create the first puzzle here.
}

void CrosswordsLevel::UseHint() {
  if (hints_left_ <= 0) return;
  --hints_left_;
  // TODO(friend): give the player a real hint.
}

void CrosswordsLevel::Reset() {
  RefillCounters();  // hints, attempts and time go back to the start
  // TODO(friend): create a NEW puzzle here.
}

void CrosswordsLevel::Display() const {
  std::cout << "\nDifficulty - " << DifficultyName(difficulty_)
            << "     time: " << timer_.Format() << "\n";
  std::cout << "Hints left: " << hints_left_ << "/"
            << HintsForDifficulty(difficulty_) << "\n";
  std::cout << "Attempts: " << (max_attempts_ - attempts_left_) << "/"
            << max_attempts_ << "\n";
  // TODO(friend): draw your puzzle here.
  std::cout << "\nR=Reset H=Hint  I=Rules  S=Save & Quit\n";
}

bool CrosswordsLevel::IsSolved() const {
  return false;  // TODO(friend)
}

bool CrosswordsLevel::IsOutOfAttempts() const { return attempts_left_ <= 0; }

Json CrosswordsLevel::ToJson() const {
  // Flat json only. TODO(friend): add your game's fields (use strings for
  // boards, for example "board":"530070000...").
  return "{\"hintsLeft\":" + std::to_string(hints_left_) +
         ",\"attemptsLeft\":" + std::to_string(attempts_left_) +
         ",\"seconds\":" + std::to_string(timer_.seconds()) + "}";
}

void CrosswordsLevel::FromJson(const Json& json) {
  hints_left_ = JsonGetInt(json, "hintsLeft");
  attempts_left_ = JsonGetInt(json, "attemptsLeft");
  timer_.set_seconds(JsonGetInt(json, "seconds"));
  // TODO(friend): restore your game's fields.
}
