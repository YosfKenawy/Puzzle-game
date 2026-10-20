#pragma once

#include "core/level.h"

constexpr int kSudokuAttempts = 6;

class SudokuLevel : public Level {
 public:
  explicit SudokuLevel(Difficulty difficulty);

  void UseHint() override;
  void Reset() override;
  void Display() const override;
  bool IsSolved() const override;
  bool IsOutOfAttempts() const override;
  Json ToJson() const override;
  void FromJson(const Json& json) override;

 private:
};
