#pragma once

#include "core/level.h"

// TODO(friend): set how many attempts one Level of your game has.
constexpr int kSudokuAttempts = 6;

class SudokuLevel : public Level {
 public:
  explicit SudokuLevel(Difficulty difficulty);

  // TODO(friend): add your game's own methods here (for example Guess()).

  // ---- Required by Level ----
  void UseHint() override;
  void Reset() override;
  void Display() const override;
  bool IsSolved() const override;
  bool IsOutOfAttempts() const override;
  Json ToJson() const override;
  void FromJson(const Json& json) override;

 private:
  // TODO(friend): add your game's data here (board, word, cards...).
};
