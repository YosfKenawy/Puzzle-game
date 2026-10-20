#pragma once

#include <string>

enum class Difficulty { kEasy, kMedium, kHard };

inline constexpr Difficulty kAllDifficulties[3] = {
    Difficulty::kEasy, Difficulty::kMedium, Difficulty::kHard};

enum class InputResult {
  kText,
  kInvalid,
  kReset,
  kHint,
  kRules,
  kSaveQuit,
};

enum class LevelOutcome {
  kSolved,
  kFailed,
  kSavedAndQuit,
};

struct PlayResult {
  LevelOutcome outcome;
  int seconds;
};

using Json = std::string;

inline int HintsForDifficulty(Difficulty difficulty) {
  switch (difficulty) {
    case Difficulty::kEasy:
      return 3;
    case Difficulty::kMedium:
      return 2;
    case Difficulty::kHard:
      return 1;
  }
  return 1;
}

inline std::string DifficultyKey(Difficulty difficulty) {
  switch (difficulty) {
    case Difficulty::kEasy:
      return "easy";
    case Difficulty::kMedium:
      return "medium";
    case Difficulty::kHard:
      return "hard";
  }
  return "easy";
}

inline std::string DifficultyName(Difficulty difficulty) {
  switch (difficulty) {
    case Difficulty::kEasy:
      return "Easy";
    case Difficulty::kMedium:
      return "Medium";
    case Difficulty::kHard:
      return "Hard";
  }
  return "Easy";
}
