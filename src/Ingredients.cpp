/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/Ingredients.hpp"
#include "../include/IPizzas.hpp"
#include <iostream>

kitchen::Ingredients::Ingredients(int timeIngredients)
{
    _timeIngredients = timeIngredients;
    regenerateEachIngredients(5);
    _start = std::chrono::steady_clock::now();
}

kitchen::Ingredients::~Ingredients()
{

}

void kitchen::Ingredients::regenerateEachIngredients(int nb)
{
    for (int i = 0; i < nb; i++) {
        _stockIngredients.push_back(kitchen::listIngredients::Doe);
        _stockIngredients.push_back(kitchen::listIngredients::Tomato);
        _stockIngredients.push_back(kitchen::listIngredients::Gruyere);
        _stockIngredients.push_back(kitchen::listIngredients::Ham);
        _stockIngredients.push_back(kitchen::listIngredients::Mushrooms);
        _stockIngredients.push_back(kitchen::listIngredients::Steak);
        _stockIngredients.push_back(kitchen::listIngredients::Eggplant);
        _stockIngredients.push_back(kitchen::listIngredients::Goat_Cheese);
        _stockIngredients.push_back(kitchen::listIngredients::Chief_Love);
    }
}

void kitchen::Ingredients::checkRegeneration(void)
{
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(end - _start).count() >= _timeIngredients) {
        regenerateEachIngredients(1);
        _start = std::chrono::steady_clock::now();
    }
}

bool kitchen::Ingredients::takeIngredientForPizzas(kitchen::listIngredients ingredient)
{
    checkRegeneration();
    for (int i = 0; i < _stockIngredients.size(); i++) {
        if (ingredient == _stockIngredients[i]) {
            _stockIngredients.erase(_stockIngredients.begin() + i);
            return (true);
        }
    }
    return (false);
}