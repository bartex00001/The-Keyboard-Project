#pragma once

#include <cstdint>
#include <cstring>

#include "KeyboardDriver/Key.hpp"

namespace BufferManager
{

inline std::uint8_t keyBuffer[6]{};
inline std::uint8_t modifiers;

void clearBuffer();
void addKey(const Key& key);

void sendReport();

}
