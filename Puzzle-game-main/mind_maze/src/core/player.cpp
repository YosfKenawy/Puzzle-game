#include "core/player.h"

#include <utility>

namespace {

std::string SlotKey(const std::string& game_key, Difficulty difficulty) {
  return game_key + "/" + DifficultyKey(difficulty);
}

}

Player::Player() {}

Player::Player(const std::string& name) : name_(name) {}

const std::string& Player::name() const { return name_; }

Level* Player::Slot(const std::string& game_key, Difficulty difficulty) const {
  auto it = slots_.find(SlotKey(game_key, difficulty));
  if (it == slots_.end()) return nullptr;
  return it->second.get();
}

void Player::SetSlot(const std::string& game_key, Difficulty difficulty,
                     LevelPtr level) {
  slots_[SlotKey(game_key, difficulty)] = std::move(level);
}

void Player::ClearSlot(const std::string& game_key, Difficulty difficulty) {
  slots_.erase(SlotKey(game_key, difficulty));
}

bool Player::HasSavedLevel(const std::string& game_key) const {
  for (Difficulty difficulty : kAllDifficulties) {
    if (Slot(game_key, difficulty) != nullptr) return true;
  }
  return false;
}

void Player::AutoSave() const {
  if (auto_save_) auto_save_();
}

void Player::set_auto_save(std::function<void()> auto_save) {
  auto_save_ = std::move(auto_save);
}
