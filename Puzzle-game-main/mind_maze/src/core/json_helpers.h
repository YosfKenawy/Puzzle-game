#pragma once

#include <string>

#include "core/types.h"

std::string JsonGetString(const Json& json, const std::string& key);

int JsonGetInt(const Json& json, const std::string& key);

Json JsonGetObject(const Json& json, const std::string& key);
