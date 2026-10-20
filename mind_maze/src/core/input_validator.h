#pragma once

#include <string>

#include "core/types.h"

// The ONLY way a game may read user input. Never use std::cin directly.
// Every function re-asks on bad input, so invalid input never exits the game.
// Owner: App owner. Game owners must NOT edit this file.
class InputValidator {
 public:
  InputValidator() = delete;  // utility class: only static functions

  // Name rules: letters and digits only, 1 to 15 characters.
  static bool IsValidName(const std::string& name);

  // Asks "Enter your name:" until the name is valid. Returns it lowercase.
  static std::string ReadName();

  // Asks until the player types a whole number from min to max.
  static int ReadMenuChoice(int min, int max);

  // Reads one command key and returns it in UPPERCASE (for example 'R').
  static char ReadCommand();

  // Use this inside a Level loop. Reads one line:
  //  - "R", "H", "I" or "S" (any case) -> kReset, kHint, kRules, kSaveQuit
  //  - empty line                      -> kInvalid
  //  - anything else                   -> kText, and *text holds the line
  static InputResult ReadLevelInput(std::string* text);
};
