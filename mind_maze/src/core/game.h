#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/level.h"
#include "core/types.h"

class Player;  // owned by the App (see player.h)

// One game of Mind Maze (abstract). Every game inherits from this.
// Owner: App owner. Game owners must NOT edit this file.
//
// A game must NOT handle menus, saving to disk, or high scores.
// It only plays Levels and reports the result to the caller.
class Game {
 public:
  virtual ~Game() = default;

  const std::string& key() const { return key_; }    // for example "wordscramble"
  const std::string& name() const { return name_; }  // for example "Word Scramble"

  // ---- Every game MUST implement these ----
  virtual int Attempts() const = 0;            // attempts per Level
  virtual std::string HowToPlay() const = 0;   // one line, for the Rules screen
  virtual LevelPtr CreateLevel(Difficulty difficulty) const = 0;
  virtual LevelPtr LoadLevel(const Json& json, Difficulty difficulty) const = 0;

  // Plays ONE Level and runs its whole loop (screen, keys, timer).
  // Resumes the Level saved in the player's slot, or starts a new one.
  // See WordScramble::Play for the exact steps.
  virtual PlayResult Play(Difficulty difficulty, Player& player) = 0;

  // ---- Shared (already written, do not override) ----
  void ShowRules() const;   // Rules & Scoring screen
  int PlayAgainMenu() const;  // returns 1 = play again, 2 = change, 3 = back

 protected:
  Game(const std::string& key, const std::string& name);

  std::string key_;
  std::string name_;
};

// All games of the App (created in app/game_list.cpp).
using GameList = std::vector<std::unique_ptr<Game>>;
