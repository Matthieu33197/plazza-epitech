/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#ifndef __COOKS_HPP__
#define __COOKS_HPP__

#include <thread>
#include <mqueue.h>
#include "../include/Kitchen.hpp"
#include "../include/Commands.hpp"
#include "../include/Mutex.hpp"
#include "../include/Ingredients.hpp"

namespace kitchen
{
    struct infosForThreads
    {
        mqd_t input;
        mqd_t output;
        float coeff;
        int timeIngredients;
        plazza::Mutex mutex;
    };
    class Cooks
    {
        public:
            Cooks(){};
            ~Cooks(){};
            void takeIngredientsForRegina(kitchen::Ingredients &ingredient);
            void takeIngredientsForMargarita(kitchen::Ingredients &ingredient);
            void takeIngredientsForAmericana(kitchen::Ingredients &ingredient);
            void takeIngredientsForFantasia(kitchen::Ingredients &ingredient);
            void cookFunction(mqd_t input, mqd_t output, float coeff, int timeIngredients, plazza::Mutex &mutexIN, plazza::Mutex &mutexOUT, plazza::Mutex &mutexIngredients, kitchen::Ingredients &ingredient);
            float calculatePreparationTime(struct pizzas::infosCommands command, float coeff);
            void takeIngredientsForPizzas(struct pizzas::infosCommands unpackCommand, kitchen::Ingredients &ingredient);
        private:
    };
}

#endif