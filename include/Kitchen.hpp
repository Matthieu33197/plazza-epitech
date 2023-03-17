/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#ifndef __KITCHEN_HPP__
#define __KITCHEN_HPP__

#include <vector>
#include <thread>
#include "../include/Cooks.hpp"
#include "../include/IPizzas.hpp"
#include "../include/IPC.hpp"
#include "../include/Ingredients.hpp"
#include <string>

namespace plazza
{
    class Kitchen
    {
        public:
            Kitchen(int id, float coeff, int nbCooks, int timeIngredients);
            ~Kitchen();
            void setCooksThreads(void);
            void configIpcKitchen(void);
        private:
            int _id;
            mqd_t _input;
            mqd_t _output;
            std::unique_ptr<plazza::IPC> _ipc;
            std::vector<std::thread> _listCooks;
            float _coeff;
            int _nbCooks;
            int _timeIngredients;
    };
}

#endif