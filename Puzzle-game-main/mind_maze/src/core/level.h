#pragma once

#include <memory>

#include "core/timer.h"
#include "core/types.h"

class Level {
 public:
  virtual ~Level() = default;

  virtual void UseHint() = 0;
  virtual void Reset() = 0;
  virtual void Display() const = 0;
  virtual bool IsSolved() const = 0;
  virtual bool IsOutOfAttempts() const = 0;
  virtual Json ToJson() const = 0;
  virtual void FromJson(const Json& json) = 0;

  Difficulty difficulty() const { return difficulty_; }
  int hints_left() const { return hints_left_; }
  int attempts_left() const { return attempts_left_; }
  Timer& timer() { return timer_; }

 protected:
  Level(Difficulty difficulty, int max_attempts);

  void RefillCounters();

  Difficulty difficulty_;
  int max_attempts_;
  int hints_left_;
  int attempts_left_;
  Timer timer_;
};

using LevelPtr = std::unique_ptr<Level>;
