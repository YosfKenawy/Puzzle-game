#pragma once

#include <memory>

#include "core/timer.h"
#include "core/types.h"

// One playable Level of any game (abstract).
// Owner: App owner. Game owners must NOT edit this file.
// Each game writes its own subclass, for example WordScrambleLevel.
class Level {
 public:
  virtual ~Level() = default;

  // ---- Every game MUST implement these ----
  virtual void UseHint() = 0;              // spend one hint (if any are left)
  virtual void Reset() = 0;                // new puzzle; call RefillCounters()
  virtual void Display() const = 0;        // draw the in-game screen
  virtual bool IsSolved() const = 0;
  virtual bool IsOutOfAttempts() const = 0;
  virtual Json ToJson() const = 0;         // exact state, including timer_.seconds()
  virtual void FromJson(const Json& json) = 0;  // restore that state

  // ---- Shared (already written) ----
  Difficulty difficulty() const { return difficulty_; }
  int hints_left() const { return hints_left_; }
  int attempts_left() const { return attempts_left_; }
  Timer& timer() { return timer_; }

 protected:
  Level(Difficulty difficulty, int max_attempts);

  // Refills hints and attempts and sets the time back to 0.
  void RefillCounters();

  Difficulty difficulty_;
  int max_attempts_;
  int hints_left_;
  int attempts_left_;
  Timer timer_;
};

using LevelPtr = std::unique_ptr<Level>;
