/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/Core.hpp"

void help(void)
{
    std::cout << "USAGE: ./panoramix [m] [c] [t]\n" << std::endl;
    std::cout << "\tm : multiplier for the cooking time of the"
    " pizzas" << std::endl;
    std::cout << "\tc : the number of cooks per kitchen" << std::endl;
    std::cout << "\tt : the time in milliseconds, used by the "
    "kitchen stock to replace ingredients" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 4) {
        help();
        return (84);
    }
    for (int y = 1; y != ac; y++) {
        for (int x = 0; av[y][x] != '\0'; x++) {
            if (av[y][x] < '0' || av[y][x] > '9'){
                std::cout << "The arguments must be numbers !" << std::endl;
                return (84);
            }
        }
    }
    if (atoi(av[2]) < 1) {
        std::cout << "The second argument must be equal or superior than 1" << std::endl;
        return (84);
    }
    plazza::Core core(atof(av[1]), atoi(av[2]), atoi(av[3]));

    return (0);
}