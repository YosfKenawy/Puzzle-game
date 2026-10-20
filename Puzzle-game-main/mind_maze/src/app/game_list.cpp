#include "app/game_list.h"

#include <memory>

#include "games/memory_cards/memory_cards.h"
#include "games/sudoku/sudoku.h"
#include "games/crosswords/crosswords.h"
#include "games/word_scramble/word_scramble.h"
#include "games/wordle/wordle.h"

GameList CreateAllGames() {
  GameList games;
  games.push_back(std::make_unique<Wordle>());
  games.push_back(std::make_unique<WordScramble>());
  games.push_back(std::make_unique<Sudoku>());
  games.push_back(std::make_unique<MemoryCards>());
  games.push_back(std::make_unique<Crosswords>());
  return games;
}
