#pragma once

#include <chrono>
#include <string>

// Counts the seconds spent on one Level.
// Owner: App owner. Game owners must NOT edit this file.
class Timer {
 public:
  Timer();

  void Start();  // start (or resume) counting
  void Stop();   // pause counting; the time so far is kept
  void set_seconds(int seconds);  // restore a saved time, or reset to 0
  int seconds() const;            // total seconds so far
  std::string Format() const;     // "m:ss", for example "0:17"

 private:
  int seconds_;  // time already counted before the current Start()
  bool running_;
  std::chrono::steady_clock::time_point started_at_;
};
