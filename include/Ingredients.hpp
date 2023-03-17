/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#ifndef __INGREDIENTS_HPP__
#define __INGREDIENTS_HPP__

#include <vector>
#include <chrono>
#include <string>

namespace kitchen {
    enum listIngredients {
        Doe = 1,
        Tomato = 2,
        Gruyere = 3,
        Ham = 4,
        Mushrooms = 5,
        Steak = 6,
        Eggplant = 7,
        Goat_Cheese = 8,
        Chief_Love = 9,
    };
    class Ingredients
    {
        public:
            Ingredients(int timeIngredients);
            ~Ingredients();
            void regenerateEachIngredients(int nb);
            bool takeIngredientForPizzas(kitchen::listIngredients ingredient);
            void checkRegeneration(void);
        private:
            std::chrono::steady_clock::time_point _start;
            std::vector<kitchen::listIngredients> _stockIngredients;
            int _timeIngredients;

    };
}

#endif