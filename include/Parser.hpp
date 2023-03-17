/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#ifndef __PARSER__
#define __PARSER__

#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include "../include/Core.hpp"

namespace plazza
{
    class Parser
    {
        public:
            Parser(){};
            ~Parser(){};
            std::vector<struct infosCommandsString> parseCommand(std::string cmd);
            std::vector<std::string> cutEachCommand(std::string cmd);
        private:
    };
}

#endif