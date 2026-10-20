#pragma once

#include <string>

#include "core/level.h"

constexpr int kWordScrambleAttempts = 6;

class WordScrambleLevel : public Level {
 public:
  explicit WordScrambleLevel(Difficulty difficulty);

  bool Guess(const std::string& answer);
  const std::string& word() const;

  void UseHint() override;
  void Reset() override;
  void Display() const override;
  bool IsSolved() const override;
  bool IsOutOfAttempts() const override;
  Json ToJson() const override;
  void FromJson(const Json& json) override;

 private:
  void PickNewWord();

  std::string word_;
  std::string scrambled_;
  bool solved_;
};
