#pragma once

#include <map>
#include <string>
#include <vector>

#include "core/game.h"
#include "core/score_entry.h"
#include "core/types.h"

// All players' results, stored in highscores.json (one list per game and
// difficulty). The Overall list is calculated from the three lists.
class HighScores {
 public:
  HighScores(const std::string& file_path, const GameList& games);

  void Load();
  void Save() const;

  // Adds one solved Level to the player's total, then saves the file.
  void RecordSolve(const std::string& game_key, Difficulty difficulty,
                   const std::string& name, int seconds);

  std::vector<ScoreEntry> Top10(const std::string& game_key,
                                Difficulty difficulty) const;
  std::vector<ScoreEntry> Overall(const std::string& game_key) const;

  // The player's entry in one list, or nullptr if there is none yet.
  const ScoreEntry* Find(const std::string& game_key, Difficulty difficulty,
                         const std::string& name) const;

  void Show(const Game& game, Difficulty difficulty) const;
  void ShowOverall(const Game& game) const;

  // Average time as "m:ss".
  static std::string FormatAverage(const ScoreEntry& entry);

 private:
  static std::string ListKey(const std::string& game_key, Difficulty difficulty);
  void PrintTable(const std::string& title,
                  const std::vector<ScoreEntry>& list) const;

  std::string file_path_;
  std::vector<std::string> game_keys_;
  // key: "<game_key>/<difficulty>". The order inside a list is the order
  // in which players got their first solve (used to break ties).
  std::map<std::string, std::vector<ScoreEntry>> entries_;
};
