#include <pico/stdlib.h>

#include "KeyboardDriver/KeyMatrix.hpp"
#include "KeyboardDriver/BufferManager.hpp"

namespace KeyMatrix
{

constexpr std::uint8_t const inputLines[]{
    13, 12
};
constexpr std::size_t inputLinesCount{ sizeof inputLines / sizeof *inputLines };

constexpr std::uint8_t const outputLines[]{
    18, 19
};
constexpr std::size_t outputLinesCount{ sizeof outputLines / sizeof *outputLines };

constexpr Key keyMatrix[inputLinesCount][outputLinesCount]{
    {
        { KEY_A }, { KEY_B }
    },
    {
        { KEY_C }, { KEY_NONE, KEY_MOD_LSHIFT }
    }
};


void initInputLines()
{
    for (std::size_t i{}; i < inputLinesCount; ++i)
    {
        gpio_init(inputLines[i]);
        gpio_set_dir(inputLines[i], GPIO_IN);
        gpio_pull_down(inputLines[i]);
    }
}

void initOutputLines()
{
    for (std::size_t i{}; i < outputLinesCount; ++i)
    {
        gpio_init(outputLines[i]);
        gpio_set_dir(outputLines[i], GPIO_OUT);
        gpio_put(outputLines[i], 0);
    }
}

void initKeyMatrix()
{
    initInputLines();
    initOutputLines();
}

void scanKeyMatrix()
{
    for(int i{}; i < KeyMatrix::outputLinesCount; i++)
    {
        gpio_put(KeyMatrix::outputLines[i], 1);

        sleep_us(1); // Wait for the diodes to switch

        for(int j{}; j < KeyMatrix::inputLinesCount; j++)
        {
            if(gpio_get(KeyMatrix::inputLines[j]))
            {
                BufferManager::addKey(KeyMatrix::keyMatrix[j][i]);
            }
        }
        gpio_put(KeyMatrix::outputLines[i], 0);
    }
}

} // namespace KeyMatrix