#pragma once

#include "core/level.h"

constexpr int kCrosswordsAttempts = 6;

class CrosswordsLevel : public Level {
 public:
  explicit CrosswordsLevel(Difficulty difficulty);

  void UseHint() override;
  void Reset() override;
  void Display() const override;
  bool IsSolved() const override;
  bool IsOutOfAttempts() const override;
  Json ToJson() const override;
  void FromJson(const Json& json) override;

 private:
};
