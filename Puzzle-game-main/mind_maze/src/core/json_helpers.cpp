#include "core/json_helpers.h"

#include <cctype>
#include <cstdlib>

namespace {

void SkipSpaces(const Json& json, std::size_t* pos) {
  while (*pos < json.size() &&
         std::isspace(static_cast<unsigned char>(json[*pos]))) {
    ++(*pos);
  }
}

std::size_t FindValueStart(const Json& json, const std::string& key) {
  const std::string pattern = "\"" + key + "\"";
  std::size_t search_from = 0;
  while (true) {
    std::size_t pos = json.find(pattern, search_from);
    if (pos == std::string::npos) return std::string::npos;
    std::size_t after = pos + pattern.size();
    SkipSpaces(json, &after);
    if (after < json.size() && json[after] == ':') {
      ++after;
      SkipSpaces(json, &after);
      return after;
    }
    search_from = pos + 1;
  }
}

}

std::string JsonGetString(const Json& json, const std::string& key) {
  std::size_t pos = FindValueStart(json, key);
  if (pos == std::string::npos || pos >= json.size() || json[pos] != '"') {
    return "";
  }
  std::size_t end = json.find('"', pos + 1);
  if (end == std::string::npos) return "";
  return json.substr(pos + 1, end - pos - 1);
}

int JsonGetInt(const Json& json, const std::string& key) {
  std::size_t pos = FindValueStart(json, key);
  if (pos == std::string::npos) return 0;
  return std::atoi(json.c_str() + pos);
}

Json JsonGetObject(const Json& json, const std::string& key) {
  std::size_t pos = FindValueStart(json, key);
  if (pos == std::string::npos || pos >= json.size()) return "";
  if (json[pos] != '{' && json[pos] != '[') return "";

  int depth = 0;
  bool in_string = false;
  for (std::size_t i = pos; i < json.size(); ++i) {
    char c = json[i];
    if (c == '"') in_string = !in_string;
    if (in_string) continue;
    if (c == '{' || c == '[') ++depth;
    if (c == '}' || c == ']') {
      --depth;
      if (depth == 0) return json.substr(pos, i - pos + 1);
    }
  }
  return "";
}
