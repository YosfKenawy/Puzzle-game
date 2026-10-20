#pragma once

#include <functional>
#include <map>
#include <string>

#include "core/level.h"
#include "core/types.h"

class Player {
 public:
  Player();
  explicit Player(const std::string& name);

  const std::string& name() const;

  Level* Slot(const std::string& game_key, Difficulty difficulty) const;
  void SetSlot(const std::string& game_key, Difficulty difficulty,
               LevelPtr level);
  void ClearSlot(const std::string& game_key, Difficulty difficulty);
  bool HasSavedLevel(const std::string& game_key) const;

  void AutoSave() const;
  void set_auto_save(std::function<void()> auto_save);

 private:
  std::string name_;
  std::map<std::string, LevelPtr> slots_;
  std::function<void()> auto_save_;
};
