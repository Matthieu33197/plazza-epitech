/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#ifndef __CORE__
#define __CORE__

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "../include/Reception.hpp"
#include "../include/Parser.hpp"

namespace plazza
{
    class Core
    {
        public:
            Core(float multiplier, int nbCooks, int timeIngredients);
            ~Core();
            std::string getCommand(void);
            bool isCorrectCommand(std::string cmd);
            void Loop(void);
            void handle_ctrlc(void);
        private:
            std::unique_ptr<plazza::Reception> _reception;
            std::vector<struct infosCommandsString> _listCommand;
            float _multiplier;
            int _nbCooks;
            int _timeIngredients;

    };
}

#endif