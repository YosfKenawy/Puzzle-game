# Mind Maze: Final Design

## 1. Start

```
Enter your name: zeyad
```

- Known name: load the save file (`saves/zeyad.json`).
- Unknown name: create a new player.
- Names are case-insensitive and stored in lowercase.
- Name rules: letters and digits only, 1 to 15 characters. Invalid or empty input is re-asked.

## 2. Main menu

Each game shows `[In progress]` if the player has a saved Level in at least one difficulty, otherwise `[New]`.

```
=== MIND MAZE ===
1. Wordle             [New]
2. Word Scramble      [In progress]
3. Sudoku             [New]
4. Memory Cards       [New]
5. Word Crossroads    [New]
0. Exit
```

## 3. Game menu

Each difficulty shows whether it has a saved Level.

```
=== WORD SCRAMBLE ===
1. Easy Level
2. Medium Level   [In progress]
3. Hard Level
4. High Scores
5. Rules & Scoring
6. Back
```

If the player picks a difficulty that has a saved Level:

```
You have a saved Level (Medium).
1. Continue
2. Start new (erases the saved Level)
3. Back
```

## 4. Difficulty and Hints

| Difficulty | Hints |
| ---------- | ----- |
| Easy       | 3     |
| Medium     | 2     |
| Hard       | 1     |

- what makes a level harder is fewer Hints.
- Attempts are defined per game and shown on the Rules & Scoring screen (Word Scramble: 6).
- There are no points. Progress is measured by Levels solved and average time (see section 8).

## 5. In-game screen

```
Difficulty - Medium     time: 0:17
Hints left: 1/2
Attempts: 2/6
Scrambled: P L E A P

R=Reset H=Hint  I=Rules  S=Save & Quit
```

- **Reset**: restarts the Level with a new word and refills attempts, hints and time.
- **Hint:** uses one hint.
- **Rules (I):** shows the Rules & Scoring screen without leaving the Level.
- **Save & Quit:** saves the exact current state, including the time spent since the last action, then returns to the menu. It does not depend on auto-save.
- The timer counts the time spent on the current Level and is used for the average time in the high scores.
- Answers are case-insensitive.

## 6. Rules & Scoring screen

```
How to play: unscramble the letters to form a word.
Attempts Allowed: 6
Hints per Difficulty: 3 (easy) / 2 (medium) / 1 (hard)
Ranking: most Levels solved, then lowest average time.
```

Every game has its own version of the "How to play" line and its own attempts line.

## 7. After a Level

- **Solved:** show the time taken and the player's updated stats (Levels solved, average time) for this difficulty, clear the saved Level in this slot, then show the Play again menu.
- **Out of attempts:** show the answer, clear the saved Level in this slot, then show the Play again menu. A failed Level does not count as solved.
- **Quit mid-Level:** progress resumes at the Level with the same state (Word, Hints, Attempts, Time).

### Play again menu

```
1. Play again (same difficulty)
2. Change difficulty
3. Back to game menu
```

## 8. High scores

- Four lists per game: one per difficulty (Easy, Medium, Hard) and one Overall list for the whole game.
- Each entry shows: name, number of Levels solved, average time.
- Ranking:
  - most Levels solved first. If two players have the same number solved, the lower average time ranks higher,
  - if there is a tie also in average time -which is very rare- ranks higher is whoever reached it first according to `highscores.json`.
- The top 10 are displayed for each list.
- **Overall list:** adds up each player's results from all three difficulties. Solved = Easy + Medium + Hard solved, and average time = total seconds of all three divided by total solved. It is ranked the same way (most solved, then lowest average time).
- Choosing "High Scores" in the game menu asks which difficulty to show:

```
=== WORD SCRAMBLE - HIGH SCORES ===
1. Easy
2. Medium
3. Hard
4. Overall
5. Back
```

```
=== WORD SCRAMBLE - HARD - HIGH SCORES ===
#   Name     Solved   Avg time
1.  zeyad     12       0:28
2.  mohammed  12       0:35
3.  Bassel     9        0:21
4.  Yousef     8        0:21
```

```
=== WORD SCRAMBLE - OVERALL - HIGH SCORES ===
#   Name     Solved   Avg time
1.  zeyad    30       0:41
2.  sarah     27       0:33
3.  omar     27       0:38
```

- Each solved Level adds to the player's total for that game and difficulty. The average time is total time divided by Levels solved.
- The Overall list is calculated from the three difficulty lists, so it needs no extra storage in `highscores.json`.
- Stored in a separate file, `highscores.json`, because all players are ranked together:

```json
{
  "wordscramble": {
    "easy": [],
    "medium": [],
    "hard": [{ "name": "zeyad", "solved": 12, "totalSeconds": 336 }]
  }
}
```

## 9. Save file (JSON) and auto-save

One file per player: `saves/<name>.json`. Each game has 3 save slots, one per difficulty, and `null` means no saved Level in that slot.

```json
{
  "name": "zeyad",
  "games": {
    "wordscramble": {
      "easy": null,
      "medium": {
        "word": "apple",
        "scrambled": "pleap",
        "hintsLeft": 1,
        "attemptsLeft": 4,
        "seconds": 17
      },
      "hard": null
    },
    "wordle": { "easy": null, "medium": null, "hard": null },
    "sudoku": { "easy": null, "medium": null, "hard": null },
    "memorycards": { "easy": null, "medium": null, "hard": null },
    "crossroads": { "easy": null, "medium": null, "hard": null }
  }
}
```

- **Auto-Save:** the game saves when a Level starts and after every action (guess, hint, reset). Closing the window or pressing Ctrl+C loses nothing. When the player opens the game again, every saved Level is still there.
- **Save & Quit** saves everything again at that moment, so the timer is saved exactly, including the time since the last action.
- If the game is closed without Save & Quit (window closed, Ctrl+C, crash), the last auto-save is restored. The timer then resumes from that auto-save, so time spent after the last action is not counted.
- Missing file: treat as a new player and create one.

## 10. Quitting

- **Save & Quit** (S in a Level) saves the exact state and time, then returns to the menu.
- Closing the window or pressing Ctrl+C is safe: the last auto-save is restored on the next start. Only the time since the last action is lost.
- Invalid input never exits the game; it re-asks.
