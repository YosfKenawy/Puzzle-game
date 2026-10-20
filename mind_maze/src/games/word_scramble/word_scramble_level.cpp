#include "games/word_scramble/word_scramble_level.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <vector>

#include "core/json_helpers.h"

namespace {

std::string ToLower(std::string text) {
  for (char& c : text) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  }
  return text;
}

}  // namespace

WordScrambleLevel::WordScrambleLevel(Difficulty difficulty)
    : Level(difficulty, kWordScrambleAttempts), solved_(false) {
  PickNewWord();
}

bool WordScrambleLevel::Guess(const std::string& answer) {
  if (ToLower(answer) == word_) {  // answers are case-insensitive
    solved_ = true;
    return true;
  }
  if (attempts_left_ > 0) --attempts_left_;
  return false;
}

const std::string& WordScrambleLevel::word() const { return word_; }

void WordScrambleLevel::UseHint() {
  if (hints_left_ <= 0) return;
  --hints_left_;
  // TODO: do something useful here
}

void WordScrambleLevel::Reset() {
  RefillCounters();  // hints, attempts and time go back to the start
  solved_ = false;
  PickNewWord();     // new word
}

void WordScrambleLevel::Display() const {
  std::cout << "\nDifficulty - " << DifficultyName(difficulty_)
            << "     time: " << timer_.Format() << "\n";
  std::cout << "Hints left: " << hints_left_ << "/"
            << HintsForDifficulty(difficulty_) << "\n";
  std::cout << "Attempts: " << (max_attempts_ - attempts_left_) << "/"
            << max_attempts_ << "\n";
  std::cout << "Scrambled:";
  for (char c : scrambled_) {
    std::cout << " " << static_cast<char>(std::toupper(
                            static_cast<unsigned char>(c)));
  }
  std::cout << "\n\nR=Reset H=Hint  I=Rules  S=Save & Quit\n";
}

bool WordScrambleLevel::IsSolved() const { return solved_; }

bool WordScrambleLevel::IsOutOfAttempts() const { return attempts_left_ <= 0; }

Json WordScrambleLevel::ToJson() const {
  // Same fields as the save file in the design doc.
  return "{\"word\":\"" + word_ + "\",\"scrambled\":\"" + scrambled_ +
         "\",\"hintsLeft\":" + std::to_string(hints_left_) +
         ",\"attemptsLeft\":" + std::to_string(attempts_left_) +
         ",\"seconds\":" + std::to_string(timer_.seconds()) + "}";
}

void WordScrambleLevel::FromJson(const Json& json) {
  word_ = JsonGetString(json, "word");
  scrambled_ = JsonGetString(json, "scrambled");
  hints_left_ = JsonGetInt(json, "hintsLeft");
  attempts_left_ = JsonGetInt(json, "attemptsLeft");
  timer_.set_seconds(JsonGetInt(json, "seconds"));
  solved_ = false;
}

void WordScrambleLevel::PickNewWord() {
  // TODO: replace this tiny list with a bigger word list.
  static const std::vector<std::string> kWords = {"apple", "plane", "house",
                                                  "chair", "bread", "river"};
  static std::mt19937 engine{std::random_device{}()};

  word_ = kWords[engine() % kWords.size()];
  scrambled_ = word_;
  // TODO: make sure the scrambled word is never equal to the word.
  std::shuffle(scrambled_.begin(), scrambled_.end(), engine);
}
