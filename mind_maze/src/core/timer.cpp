#include "core/timer.h"

Timer::Timer() : seconds_(0), running_(false) {}

void Timer::Start() {
  if (running_) return;
  running_ = true;
  started_at_ = std::chrono::steady_clock::now();
}

void Timer::Stop() {
  if (!running_) return;
  seconds_ = seconds();
  running_ = false;
}

void Timer::set_seconds(int seconds) {
  seconds_ = seconds;
  if (running_) started_at_ = std::chrono::steady_clock::now();
}

int Timer::seconds() const {
  if (!running_) return seconds_;
  auto elapsed = std::chrono::steady_clock::now() - started_at_;
  return seconds_ +
         static_cast<int>(
             std::chrono::duration_cast<std::chrono::seconds>(elapsed).count());
}

std::string Timer::Format() const {
  int total = seconds();
  int minutes = total / 60;
  int rest = total % 60;
  return std::to_string(minutes) + ":" + (rest < 10 ? "0" : "") +
         std::to_string(rest);
}
