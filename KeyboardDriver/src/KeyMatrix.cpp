#include <pico/stdlib.h>

#include <KeyboardDriver/KeyMatrix.hpp>

namespace KeyMatrix
{

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

} // namespace KeyMatrix