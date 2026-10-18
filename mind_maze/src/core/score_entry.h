#pragma once

#include <string>

// One player's total for one game and one difficulty (used by HighScores).
// Owner: App owner. Game owners must NOT edit this file.
class ScoreEntry {
 public:
  ScoreEntry(const std::string& name, int solved, int total_seconds);

  const std::string& name() const;
  int solved() const;
  int total_seconds() const;

  double AverageSeconds() const;  // total_seconds / solved (0 if nothing solved)
  void AddSolve(int seconds);

 private:
  std::string name_;
  int solved_;
  int total_seconds_;
};
