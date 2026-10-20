## Build and run (from the project root)
```
g++ -std=c++17 -Wall -Wextra -Isrc src/main.cpp src/core/*.cpp src/app/*.cpp src/games/*/*.cpp -o mind_maze_app
./mind_maze_app
```
Try: play a Level, press H, R, I, S (then continue), solve it, and fail it.

Saves go to `saves/` and scores to `highscores.json`.
