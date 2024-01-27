#include <iostream>
#include "lib/inc/sys_gpio.hpp"

#define LED_PIN 24

int main(int argc, char const *argv[])
{
    GPIO gpio;

    gpio.export_pin(LED_PIN);
    gpio.set_gpio_direction(LED_PIN, SYS_GPIO_OUTPUT);

    while (1)
    {
        gpio.write_gpio(LED_PIN, SYS_GPIO_HIGH);
        usleep(500000);
        gpio.write_gpio(LED_PIN, SYS_GPIO_LOW);
        usleep(500000);
    }
    return 0;
}
