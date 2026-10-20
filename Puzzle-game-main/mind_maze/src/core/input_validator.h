#pragma once

#include <string>

#include "core/types.h"

class InputValidator {
 public:
  InputValidator() = delete;

  static bool IsValidName(const std::string& name);

  static std::string ReadName();

  static int ReadMenuChoice(int min, int max);

  static char ReadCommand();

  static InputResult ReadLevelInput(std::string* text);
};
