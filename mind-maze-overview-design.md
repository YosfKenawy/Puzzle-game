# Mind Maze: Final Design

## 1. Start
```
Enter your name: zeyad
```
- Known name: load the save file.
- Unknown name: create a new player.
- Names are case-insensitive and stored in lowercase.

## 2. Main menu
```
=== MIND MAZE ===
1. Wordle        (Continue Level 3)
2. Word Scramble (Continue Level 5)
3. Sudoku        (New)
0. Exit
```
Each game shows the saved Level, or "New" if the player hasn't started it.

## 3. Game menu
```
=== WORD SCRAMBLE ===
1. Continue (Level 5)
2. New Game
3. High Scores
4. Rules & Scoring
5. Back
```
- **New Game:** warns "This will erase your progress. Are you sure? (y/n)".
- **Continue:** hidden if there is no save.

## 4. Levels and difficulty
| Levels | Difficulty | Base points | Each hint | Reset |
|---|---|---|---|---|
| 1-3 | Easy | 10 | -2 | -3 |
| 4-6 | Medium | 20 | -4 | -6 |
| 7-9 | Hard | 30 | -6 | -9 |
| 10 | Insane | 50 | -10 | -15 |

Every Level has **3 attempts** and **3 hints**.

## 5. In-game screen
```
Level 5/10 - Medium     Score: 45
Attempts left: 3/3      Hints left: 2/3

Scrambled: P L E A P

R=Reset  H=Hint  I=Rules  S=Save & Quit
```
- **Reset:** restarts the Level with a new word and refills attempts and hints. Points already lost to hints stay deducted, and the reset penalty is applied.
- **Hint:** costs points and uses one hint.
- **Rules (I):** shows the Rules & Scoring screen without leaving the Level.
- **Save & Quit:** saves progress and returns to the menu.
- No skip option.

## 6. Rules & Scoring screen
```
How to play: unscramble the letters to form a word.
Attempts per Level: 3
Hints per Level: 3 (each costs 20% of Level points)
Reset: 30% of Level points (refills attempts and hints)
Points per Level: 10 (easy) / 20 (medium) / 30 (hard) / 50 (insane)
```
Every game has its own version of the "How to play" line.

## 7. After a Level
- **Solved:** show points earned, then go to the next Level.
- **Out of attempts:** show the answer, then retry the Level with a new word.
- **After Level 10:** show the final score, record it in the ScoreBoard, and offer New Game or Back.
- **Quit mid-Level:** progress resumes at the start of that Level with a new word.

## 8. Other details
- Every menu has a Back option, and input is validated.
- One save file per player holds progress for all games.
- High scores are kept per game, using the total score after finishing Level 10.
