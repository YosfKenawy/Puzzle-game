#pragma once

#include <string>

#include "core/level.h"

constexpr int kWordScrambleAttempts = 6;

// EXAMPLE Level. Copy this file to see what every game's Level must have.
class WordScrambleLevel : public Level {
 public:
  explicit WordScrambleLevel(Difficulty difficulty);

  // Returns true if the answer is correct. A wrong answer costs one attempt.
  bool Guess(const std::string& answer);
  const std::string& word() const;

  // ---- Required by Level ----
  void UseHint() override;
  void Reset() override;
  void Display() const override;
  bool IsSolved() const override;
  bool IsOutOfAttempts() const override;
  Json ToJson() const override;
  void FromJson(const Json& json) override;

 private:
  void PickNewWord();  // chooses word_ and scrambles it into scrambled_

  std::string word_;
  std::string scrambled_;
  bool solved_;
};
