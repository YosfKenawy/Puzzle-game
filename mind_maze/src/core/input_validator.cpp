#include "core/input_validator.h"

#include <cctype>
#include <cstdlib>
#include <iostream>

namespace {

std::string Trim(const std::string& text) {
  std::size_t first = 0;
  while (first < text.size() &&
         std::isspace(static_cast<unsigned char>(text[first]))) {
    ++first;
  }
  std::size_t last = text.size();
  while (last > first &&
         std::isspace(static_cast<unsigned char>(text[last - 1]))) {
    --last;
  }
  return text.substr(first, last - first);
}

// Reads one trimmed line. If the input stream is closed, quit cleanly.
std::string ReadLine() {
  std::string line;
  if (!std::getline(std::cin, line)) std::exit(0);
  return Trim(line);
}

}  // namespace

bool InputValidator::IsValidName(const std::string& name) {
  if (name.empty() || name.size() > 15) return false;
  for (char c : name) {
    if (!std::isalnum(static_cast<unsigned char>(c))) return false;
  }
  return true;
}

std::string InputValidator::ReadName() {
  while (true) {
    std::cout << "Enter your name: ";
    std::string name = ReadLine();
    for (char& c : name) {
      c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    if (IsValidName(name)) return name;
    std::cout << "Invalid name. Use 1 to 15 letters or digits.\n";
  }
}

int InputValidator::ReadMenuChoice(int min, int max) {
  while (true) {
    std::cout << "Choose (" << min << "-" << max << "): ";
    std::string line = ReadLine();
    bool all_digits = !line.empty() && line.size() <= 6;
    for (char c : line) {
      if (!std::isdigit(static_cast<unsigned char>(c))) all_digits = false;
    }
    if (all_digits) {
      int choice = std::atoi(line.c_str());
      if (choice >= min && choice <= max) return choice;
    }
    std::cout << "Invalid choice, try again.\n";
  }
}

char InputValidator::ReadCommand() {
  while (true) {
    std::cout << "> ";
    std::string line = ReadLine();
    if (!line.empty()) {
      return static_cast<char>(
          std::toupper(static_cast<unsigned char>(line[0])));
    }
    std::cout << "Invalid input, try again.\n";
  }
}

InputResult InputValidator::ReadLevelInput(std::string* text) {
  std::cout << "> ";
  std::string line = ReadLine();
  if (line.empty()) return InputResult::kInvalid;
  if (line.size() == 1) {
    switch (std::toupper(static_cast<unsigned char>(line[0]))) {
      case 'R':
        return InputResult::kReset;
      case 'H':
        return InputResult::kHint;
      case 'I':
        return InputResult::kRules;
      case 'S':
        return InputResult::kSaveQuit;
      default:
        break;
    }
  }
  *text = line;
  return InputResult::kText;
}
