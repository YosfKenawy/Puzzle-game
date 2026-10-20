# Mind Maze: guide for game owners

The whole app (menus, saving, high scores) is already done. Every game has a
ready folder with empty "TODO(friend)" code. You only fill in YOUR game.

## Which files you own
| Game | Folder | Files |
|------|--------|-------|
| Wordle | `src/games/wordle/` | `wordle.h/.cpp`, `wordle_level.h/.cpp` |
| Word Scramble | `src/games/word_scramble/` | (the finished example) |
| Sudoku | `src/games/sudoku/` | `sudoku.h/.cpp`, `sudoku_level.h/.cpp` |
| Memory Cards | `src/games/memory_cards/` | `memory_cards.h/.cpp`, `memory_cards_level.h/.cpp` |
| Crosswords | `src/games/crosswords/` | `crosswords.h/.cpp`, `crosswords_level.h/.cpp` |

Plus your test file `tests/test_<folder name>.cpp`.
Use `src/games/word_scramble/` as the example of a finished game.

## Files you must NOT edit
Everything in `src/core/`, `src/app/`, `src/main.cpp`, and other games' folders.
Need a change there? Ask the App owner.

## Rules
1. Your `Game` and `Level` classes already exist. Fill in every `TODO(friend)`.
2. Read input ONLY through `InputValidator`. Never use `std::cin` directly.
3. No menus, no saving to disk, no high scores in your game. The App does that.
4. `Play(difficulty, player)` plays ONE Level and returns a `PlayResult`
   (solved / failed / saved and quit + seconds). Copy the steps from
   `WordScramble::Play`: resume or create the Level, start the timer,
   `player.AutoSave()` after the start and after every action, and
   `player.ClearSlot(...)` when the Level ends (solved or failed).
5. `ToJson()` must save the exact state including `timer_.seconds()`, and
   `FromJson()` must restore it. The json must be FLAT: no nested objects,
   no arrays. Store a board as one string, like `"board":"530070000..."`.
   Read values back with `JsonGetString` / `JsonGetInt`.
6. Naming follows the Google C++ style guide (naming only): `PascalCase` for
   classes and functions, `snake_case` for variables, `trailing_underscore_`
   for class data members, `kEnumValue` for constants and enum values.

## Compile and test your game (from the project root)
With make (replace `wordle` with your folder name):
```
make test_wordle
./test_wordle
```
Without make:
```
g++ -std=c++17 -Wall -Wextra -Isrc tests/test_wordle.cpp src/core/*.cpp src/games/wordle/*.cpp -o test_wordle
```
Try: play a Level, press H, R, I, S (then continue), solve it, and fail it.

## Run the whole app
```
make
./mind_maze_app
```
Run it from the project root. Saves go to `saves/` and scores to `highscores.json`.
