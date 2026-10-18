#pragma once

#include <string>

#include "core/types.h"

// Tiny helpers to read json text written by this project.
// Build json text yourself with std::to_string and string concatenation.
// IMPORTANT: a Level's json must be FLAT: {"a":"text","b":5}. No nested
// objects and no arrays (store a board as one string, like "530070000...").
// Owner: App owner. Game owners must NOT edit this file.

// Returns the string value of "key", or "" if it is missing.
std::string JsonGetString(const Json& json, const std::string& key);

// Returns the integer value of "key", or 0 if it is missing.
int JsonGetInt(const Json& json, const std::string& key);

// Returns the {...} or [...] value of "key" as text, or "" if the key is
// missing or its value is null.
Json JsonGetObject(const Json& json, const std::string& key);
