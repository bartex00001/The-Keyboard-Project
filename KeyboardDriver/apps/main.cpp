#include <cstdint>
#include <cstdio>

#include <pico/stdlib.h>

#include <KeyboardDriver/KeyMatrix.hpp>

void readMatrix();

int main()
{
    stdio_init_all();

    initKeyMatrix();

    // remember last poll time
    std::uint64_t lastPollTime{ time_us_64() };

    while(true)
    {
        std::printf("\nKeys read:\t");
        readMatrix();
        // std::uint64_t currentTime{ time_us_64() };
        // std::uint64_t deltaTimeUs{ currentTime - lastPollTime };
        // lastPollTime = currentTime;
        // std::printf("\nLast poll time: %llu us", deltaTimeUs);
    }

    return 0;
}

void readMatrix()
{
    for(std::size_t i{}; i < outputLinesCount; ++i)
    {
        gpio_put(outputLines[i], 1);
        sleep_us(1);

        for(std::size_t j{}; j < inputLinesCount; ++j)
        {
            if(gpio_get(inputLines[j]))
            {
                std::printf("%d ", keyMatrix[j][i].code);
            }
        }

        gpio_put(outputLines[i], 0);
    }
}
