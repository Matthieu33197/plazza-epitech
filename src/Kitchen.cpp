/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/Kitchen.hpp"
#include <iostream>

plazza::Kitchen::Kitchen(int id, float coeff, int nbCooks, int timeIngredients)
{
    _id = id;
    _coeff = coeff;
    _nbCooks = nbCooks;
    _timeIngredients = timeIngredients;
    configIpcKitchen();
    kitchen::Cooks *cook = new kitchen::Cooks();
    kitchen::Ingredients ingredient(timeIngredients);
    plazza::Mutex mutexIN;
    plazza::Mutex mutexOUT;
    plazza::Mutex mutexIngredients;

    for (int i = 0; i < nbCooks; i++)
        _listCooks.push_back(std::thread(&kitchen::Cooks::cookFunction, cook, _input, _output, _coeff, _timeIngredients, std::ref(mutexIN), std::ref(mutexOUT), std::ref(mutexIngredients), std::ref(ingredient)));
    for (int i = 0; i < _listCooks.size(); i++)
        _listCooks[i].join();
    delete cook;
    std::exit(0);
}

plazza::Kitchen::~Kitchen()
{

}

void plazza::Kitchen::configIpcKitchen()
{
    struct mq_attr attr;
    std::string nameIpc("/ToKitchen " + std::to_string(_id) );

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 20;
    _output = mq_open(nameIpc.c_str(), O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), &attr);
    if (_output == -1) {
        std::cout << "Error" << std::endl;
        std::exit(84);
    }
    nameIpc.clear();
    nameIpc = "/ToReception " + std::to_string(_id);
    _input = mq_open(nameIpc.c_str(), O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), &attr);
    if (_input == -1) {
        std::cout << "Error" << std::endl;
        std::exit(84);
    }

}