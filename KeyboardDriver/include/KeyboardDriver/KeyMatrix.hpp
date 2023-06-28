#pragma once

#include <cstdint>

#include <KeyboardDriver/Key.hpp>
#include <KeyboardDriver/UsbHidKeys.hpp>

namespace KeyMatrix
{

constexpr std::size_t inputLinesCount = 2;
constexpr std::uint8_t const inputLines[]{
    13, 12
};

constexpr std::size_t outputLinesCount = 2;
constexpr std::uint8_t const outputLines[]{
    18, 19
};

constexpr Key keyMatrix[inputLinesCount][outputLinesCount]{
    {
        { KEY_A }, { KEY_B }
    },
    {
        { KEY_C }, { KEY_NONE, KEY_MOD_LSHIFT }
    }
};

void initKeyMatrix();

} // namespace KeyMatrix
