#pragma once

#include <cstdint>
#include <cstring>

#include "KeyboardDriver/Key.hpp"

namespace BufferManager
{

void clearBuffer();
void addKey(const Key& key);

void sendReport();
void fillBuffer(std::uint8_t* buffer);

}
