#pragma once

#include <functional>
#include <map>
#include <string>

#include "core/level.h"
#include "core/types.h"

// A player and their saved Levels: one slot per game and difficulty.
// Owner: App owner. Game owners must NOT edit this file.
class Player {
 public:
  Player();
  explicit Player(const std::string& name);

  const std::string& name() const;

  // Returns the saved Level, or nullptr if the slot is empty.
  Level* Slot(const std::string& game_key, Difficulty difficulty) const;
  void SetSlot(const std::string& game_key, Difficulty difficulty,
               LevelPtr level);
  void ClearSlot(const std::string& game_key, Difficulty difficulty);
  bool HasSavedLevel(const std::string& game_key) const;

  // Games call this after a Level starts and after every action.
  // It runs the function the App gave with set_auto_save() (writes the save
  // file). When testing a game alone nothing is set, so nothing happens.
  void AutoSave() const;
  void set_auto_save(std::function<void()> auto_save);

 private:
  std::string name_;
  std::map<std::string, LevelPtr> slots_;  // key: "<game_key>/<difficulty>"
  std::function<void()> auto_save_;
};
