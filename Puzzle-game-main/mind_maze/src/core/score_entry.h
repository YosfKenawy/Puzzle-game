#pragma once

#include <string>

class ScoreEntry {
 public:
  ScoreEntry(const std::string& name, int solved, int total_seconds);

  const std::string& name() const;
  int solved() const;
  int total_seconds() const;

  double AverageSeconds() const;
  void AddSolve(int seconds);

 private:
  std::string name_;
  int solved_;
  int total_seconds_;
};
