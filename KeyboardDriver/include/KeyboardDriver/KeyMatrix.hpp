#pragma once

#include <cstdint>

constexpr std::size_t inputLinesCount = 3;
constexpr std::uint8_t const inputLines[]{
    18, 19, 20
};

constexpr std::size_t outputLinesCount = 3;
constexpr std::uint8_t const outputLines[]{
    13, 12, 11
};

constexpr std::int16_t matrixCodes[inputLinesCount][outputLinesCount]{
    { 1, 2, 3 },
    { 4, 5, 6 },
    { -7, -8, -9 }
};

void initKeyMatrix();
void initInputLines();
void initOutputLines();
