// Header: System Class GPIO Cpp Driver Source File
// File Name: sys_gpio.cpp
// Author: Turgay Hopal
// Date: 24.1.2024

#include "../inc/sys_gpio.hpp"

GPIO::GPIO()
{
    set_gpio_vect.clear();
}

GPIO::~GPIO()
{
    for (int i : set_gpio_vect)
    {
        unexport_pin(i);
    }
    set_gpio_vect.clear();
}

void GPIO::export_pin(int pin)
{
    if (std::find(set_gpio_vect.begin(), set_gpio_vect.end(), pin) == set_gpio_vect.end())
    {
        // Not Contains Pin

        std::ofstream export_file(GPIO_EXPORT_PATH);
        if (!export_file.is_open())
        {
            std::cerr << "Error opening export file: " << std::endl;
            return;
        }

        export_file << pin;

        if (export_file.fail())
        {
            std::cerr << "Error opening export file: " << std::endl;
            return;
        }

        export_file.close();

        usleep(100000);

        set_gpio_vect.push_back(pin);
    }
}

void GPIO::unexport_pin(int pin)
{
    if (std::find(set_gpio_vect.begin(), set_gpio_vect.end(), pin) != set_gpio_vect.end())
    {
        // Contains Pin
        std::ofstream unexport_file(GPIO_UNEXPORT_PATH);
        if (!unexport_file.is_open())
        {
            std::cerr << "Error opening export file: " << std::endl;
            return;
        }

        unexport_file << pin;

        if (unexport_file.fail())
        {
            std::cerr << "Error opening export file: " << std::endl;
            return;
        }

        unexport_file.close();

        usleep(100000);

        set_gpio_vect.erase(std::remove(set_gpio_vect.begin(), set_gpio_vect.end(), pin), set_gpio_vect.end());
    }
}

void GPIO::set_gpio_direction(int pin, sys_gpio_direction_t direction)
{
    std::ostringstream pin_direction_path;

    pin_direction_path << GPIO_PATH << "gpio" + std::to_string(pin) << "/direction";

    std::ofstream direction_file(pin_direction_path.str());

    if (!direction_file)
    {
        std::cerr << "Error setting GPIO direction" << std::endl;
        return;
    }

    if (direction == SYS_GPIO_OUTPUT)
    {
        direction_file << "out";
    }
    else
    {
        direction_file << "in";
    }
    direction_file.close();
}

void GPIO::write_gpio(int pin, sys_gpio_value_t value)
{
    std::ostringstream pin_path;

    pin_path << GPIO_PATH << "gpio" + std::to_string(pin) << "/value";

    std::ofstream value_file(pin_path.str());

    if (!value_file)
    {
        std::cerr << "Error writing to GPIO pin" << std::endl;
        return;
    }

    if (value == SYS_GPIO_HIGH)
    {
        value_file << "1";
    }
    else
    {
        value_file << "0";
    }
    value_file.close();
}

int GPIO::read_gpio(int pin)
{
    std::ostringstream pin_path;

    pin_path << GPIO_PATH << "gpio" + std::to_string(pin) << "/value";

    std::ifstream value_file(pin_path.str());

    if (!value_file)
    {
        std::cerr << "Error writing to GPIO pin" << std::endl;
        return -1;
    }

    int value;
    value_file >> value;

    value_file.close();

    return value;
}
