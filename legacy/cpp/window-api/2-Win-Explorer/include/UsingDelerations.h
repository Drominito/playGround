#pragma once
#include <chrono>

using namespace std::literals::chrono_literals;

#define MAXPATHLEN (uint8_t)((1 << 8) - 1) // The actual Path limit of the OS is 260 chars.