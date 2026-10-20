#pragma once

#include "core/level.h"

constexpr int kMemoryCardsAttempts = 6;

class MemoryCardsLevel : public Level {
 public:
  explicit MemoryCardsLevel(Difficulty difficulty);

  void UseHint() override;
  void Reset() override;
  void Display() const override;
  bool IsSolved() const override;
  bool IsOutOfAttempts() const override;
  Json ToJson() const override;
  void FromJson(const Json& json) override;

 private:
};
