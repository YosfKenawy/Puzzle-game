#pragma once

#include <chrono>
#include <string>

class Timer {
 public:
  Timer();

  void Start();
  void Stop();
  void set_seconds(int seconds);
  int seconds() const;
  std::string Format() const;

 private:
  int seconds_;
  bool running_;
  std::chrono::steady_clock::time_point started_at_;
};
