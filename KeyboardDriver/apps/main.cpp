#include <vector>
#include <cstdint>
#include <cstdio>

#include <pico/stdlib.h>

#include <KeyboardDriver/KeyMatrix.hpp>

std::vector< std::int16_t > pressedKeys;

void readMatrix();

int main()
{
    stdio_init_all();

    initKeyMatrix();

    // remember last poll time
    std::uint64_t lastPollTime{ time_us_64() };

    while(true)
    {
        readMatrix();

        // std::uint64_t currentTime{ time_us_64() };
        // std::uint64_t deltaTimeUs{ currentTime - lastPollTime };
        // lastPollTime = currentTime;
        // std::printf("\nLast poll time: %llu us", deltaTimeUs);

        std::printf("\nPressed keys: ");
        for(const auto key : pressedKeys)
        {
            if(key < 0)
            {
                std::printf("(mod)");
            }

            std::printf("%d     ", key);
        }

        sleep_ms(10);
        pressedKeys.clear();
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
                pressedKeys.push_back(matrixCodes[j][i]);
            }
        }

        gpio_put(outputLines[i], 0);
    }
}
