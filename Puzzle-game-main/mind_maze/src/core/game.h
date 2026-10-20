#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/level.h"
#include "core/types.h"

class Player;

class Game {
 public:
  virtual ~Game() = default;

  const std::string& key() const { return key_; }
  const std::string& name() const { return name_; }

  virtual int Attempts() const = 0;
  virtual std::string HowToPlay() const = 0;
  virtual LevelPtr CreateLevel(Difficulty difficulty) const = 0;
  virtual LevelPtr LoadLevel(const Json& json, Difficulty difficulty) const = 0;

  virtual PlayResult Play(Difficulty difficulty, Player& player) = 0;

  void ShowRules() const;
  int PlayAgainMenu() const;

 protected:
  Game(const std::string& key, const std::string& name);

  std::string key_;
  std::string name_;
};

using GameList = std::vector<std::unique_ptr<Game>>;
