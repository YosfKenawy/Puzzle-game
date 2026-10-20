# make              builds the whole game      -> ./mind_maze_app
# make test_wordle  builds one game alone      -> ./test_wordle
# (test_<folder name of your game>)
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc
CORE = $(wildcard src/core/*.cpp)
APP = $(wildcard src/app/*.cpp)
GAMES = $(wildcard src/games/*/*.cpp)

mind_maze_app: src/main.cpp $(CORE) $(APP) $(GAMES)
	$(CXX) $(CXXFLAGS) src/main.cpp $(CORE) $(APP) $(GAMES) -o $@

test_%: tests/test_%.cpp $(CORE)
	$(CXX) $(CXXFLAGS) tests/test_$*.cpp $(CORE) src/games/$*/*.cpp -o $@

clean:
	rm -f mind_maze_app test_word_scramble test_wordle test_sudoku test_memory_cards test_crosswords

.PHONY: clean
