#pragma once

#include <string>

// Shared types for Mind Maze.
// Owner: App owner. Game owners must NOT edit this file.

enum class Difficulty { kEasy, kMedium, kHard };

// Handy for loops: for (Difficulty d : kAllDifficulties) { ... }
inline constexpr Difficulty kAllDifficulties[3] = {
    Difficulty::kEasy, Difficulty::kMedium, Difficulty::kHard};

// What the player typed inside a Level (see InputValidator::ReadLevelInput).
enum class InputResult {
  kText,      // a normal answer; the text is handed to the game
  kInvalid,   // empty input; the game should simply ask again
  kReset,     // R
  kHint,      // H
  kRules,     // I
  kSaveQuit,  // S
};

// How one call to Game::Play() ended.
enum class LevelOutcome {
  kSolved,
  kFailed,        // out of attempts
  kSavedAndQuit,  // the player pressed S
};

// What Game::Play() returns to the caller (the App does scores and menus).
struct PlayResult {
  LevelOutcome outcome;
  int seconds;  // time spent on the Level
};

// JSON is plain text for now (see json_helpers.h).
using Json = std::string;

// Easy = 3 hints, Medium = 2 hints, Hard = 1 hint.
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

// Lowercase key used in save files: "easy", "medium", "hard".
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

// Name shown on screen: "Easy", "Medium", "Hard".
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
