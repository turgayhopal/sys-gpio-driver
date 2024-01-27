// Header: System Class GPIO Cpp Driver Header File
// File Name: sys_gpio.hpp
// Author: Turgay Hopal
// Date: 24.1.2024

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <algorithm>

typedef enum sys_gpio_direction_e
{
    SYS_GPIO_OUTPUT,
    SYS_GPIO_INPUT
} sys_gpio_direction_t;

typedef enum sys_gpio_value_e
{
    SYS_GPIO_LOW,
    SYS_GPIO_HIGH
} sys_gpio_value_t;

class GPIO
{
private:
    std::string GPIO_PATH = "/sys/class/gpio/";
    std::string GPIO_EXPORT_PATH = "/sys/class/gpio/export";
    std::string GPIO_UNEXPORT_PATH = "/sys/class/gpio/unexport";

    std::vector<int> set_gpio_vect{NULL};

public:
    void export_pin(int pin);
    void unexport_pin(int pin);
    void set_gpio_direction(int pin, sys_gpio_direction_t direction);
    void write_gpio(int pin, sys_gpio_value_t value);
    int read_gpio(int pin);
    GPIO();
    ~GPIO();
};
