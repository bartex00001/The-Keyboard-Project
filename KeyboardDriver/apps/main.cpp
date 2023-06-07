#include <stdio.h>

#include <pico/stdlib.h>

#include <KeyboardDriver/SignalEncoder.hpp>

int main()
{
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    while(true)
    {
        printf("Led on\n");
        gpio_put(25, 1);
        sleep_ms(1000);

        printf("Led off\n");
        gpio_put(25, 0);
        sleep_ms(1000);
    }

    return 0;
}
