#pragma once

#include <cstdint>

constexpr std::size_t inputLinesCount = 2;
constexpr std::uint8_t const inputLines[]{
    13, 12
};

constexpr std::size_t outputLinesCount = 2;
constexpr std::uint8_t const outputLines[]{
    18, 19
};

constexpr std::int16_t matrixCodes[inputLinesCount][outputLinesCount]{
    { 1, 2 },
    { 3, -4 }
};

void initKeyMatrix();
void initInputLines();
void initOutputLines();
