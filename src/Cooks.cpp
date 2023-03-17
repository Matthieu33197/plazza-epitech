/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/Cooks.hpp"
#include <strings.h>
#include <iostream>


void kitchen::Cooks::cookFunction(mqd_t input, mqd_t output, float coeff, int timeIngredients, plazza::Mutex &mutexIN, plazza::Mutex &mutexOUT, plazza::Mutex &mutexIngredients, kitchen::Ingredients &ingredient)
{
    std::unique_ptr<plazza::IPC> ipc = std::make_unique<plazza::IPC>();
    std::unique_ptr<plazza::Commands> command = std::make_unique<plazza::Commands>();
    std::string packedCommand;
    struct pizzas::infosCommands unpackCommand;
    int preparationTime = 0;

    while (1) {
        mutexIngredients.lock();
        ingredient.checkRegeneration();
        mutexIngredients.unlock();
        mutexIN.lock();
        packedCommand = ipc->receive(output);
        mutexIN.unlock();
        if (strcasecmp(packedCommand.c_str(), "stop") == 0)
            break;
        unpackCommand = command->unpack(packedCommand);
        mutexIngredients.lock();
        takeIngredientsForPizzas(unpackCommand, ingredient);
        mutexIngredients.unlock();
        preparationTime = calculatePreparationTime(unpackCommand, coeff);
        std::this_thread::sleep_for(std::chrono::milliseconds(preparationTime));
        mutexOUT.lock();
        ipc->send(input, packedCommand);
        mutexOUT.unlock();
    }
}

void kitchen::Cooks::takeIngredientsForPizzas(struct pizzas::infosCommands unpackCommand, kitchen::Ingredients &ingredient)
{
    if (unpackCommand.type == 1)
        takeIngredientsForRegina(ingredient);
    else if (unpackCommand.type == 2)
        takeIngredientsForMargarita(ingredient);
    else if (unpackCommand.type == 4)
        takeIngredientsForAmericana(ingredient);
    else if (unpackCommand.type == 8)
        takeIngredientsForFantasia(ingredient);
}

void kitchen::Cooks::takeIngredientsForRegina(kitchen::Ingredients &ingredient)
{
    while (!ingredient.takeIngredientForPizzas(kitchen::Doe));
    while (!ingredient.takeIngredientForPizzas(kitchen::Tomato));
    while (!ingredient.takeIngredientForPizzas(kitchen::Gruyere));
    while (!ingredient.takeIngredientForPizzas(kitchen::Ham));
    while (!ingredient.takeIngredientForPizzas(kitchen::Mushrooms));
}

void kitchen::Cooks::takeIngredientsForMargarita(kitchen::Ingredients &ingredient)
{
    while (!ingredient.takeIngredientForPizzas(kitchen::Doe));
    while (!ingredient.takeIngredientForPizzas(kitchen::Tomato));
    while (!ingredient.takeIngredientForPizzas(kitchen::Gruyere));
}

void kitchen::Cooks::takeIngredientsForAmericana(kitchen::Ingredients &ingredient)
{
    while (!ingredient.takeIngredientForPizzas(kitchen::Doe));
    while (!ingredient.takeIngredientForPizzas(kitchen::Tomato));
    while (!ingredient.takeIngredientForPizzas(kitchen::Gruyere));
    while (!ingredient.takeIngredientForPizzas(kitchen::Steak));
}

void kitchen::Cooks::takeIngredientsForFantasia(kitchen::Ingredients &ingredient)
{
    while (!ingredient.takeIngredientForPizzas(kitchen::Doe));
    while (!ingredient.takeIngredientForPizzas(kitchen::Tomato));
    while (!ingredient.takeIngredientForPizzas(kitchen::Eggplant));
    while (!ingredient.takeIngredientForPizzas(kitchen::Goat_Cheese));
    while (!ingredient.takeIngredientForPizzas(kitchen::Chief_Love));
}

float kitchen::Cooks::calculatePreparationTime(struct pizzas::infosCommands command, float coeff)
{
    int preparationTime = 0;

    if (command.type == 1)
        preparationTime = 2000;
    else if (command.type == 2)
        preparationTime = 1000;
    else if (command.type == 4)
        preparationTime = 2000;
    else if (command.type == 8)
        preparationTime = 4000;

    preparationTime *= coeff;

    return (preparationTime);
}