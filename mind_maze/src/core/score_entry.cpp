#include "core/score_entry.h"

ScoreEntry::ScoreEntry(const std::string& name, int solved, int total_seconds)
    : name_(name), solved_(solved), total_seconds_(total_seconds) {}

const std::string& ScoreEntry::name() const { return name_; }

int ScoreEntry::solved() const { return solved_; }

int ScoreEntry::total_seconds() const { return total_seconds_; }

double ScoreEntry::AverageSeconds() const {
  if (solved_ == 0) return 0.0;
  return static_cast<double>(total_seconds_) / solved_;
}

void ScoreEntry::AddSolve(int seconds) {
  ++solved_;
  total_seconds_ += seconds;
}
