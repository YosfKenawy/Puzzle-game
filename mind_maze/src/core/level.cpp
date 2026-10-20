#include "core/level.h"

Level::Level(Difficulty difficulty, int max_attempts)
    : difficulty_(difficulty),
      max_attempts_(max_attempts),
      hints_left_(HintsForDifficulty(difficulty)),
      attempts_left_(max_attempts) {}

void Level::RefillCounters() {
  hints_left_ = HintsForDifficulty(difficulty_);
  attempts_left_ = max_attempts_;
  timer_.set_seconds(0);
}
