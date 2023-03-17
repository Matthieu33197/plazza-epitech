/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#ifndef __RECEPTION_HPP__
#define __RECEPTION_HPP__

#include "../include/Kitchen.hpp"
#include "../include/Commands.hpp"
#include "../include/IPC.hpp"
#include "../include/ErrorManagement.hpp"
#include <string>
#include <vector>
#include <unistd.h>
#include <memory>

namespace plazza
{
    struct infosCommandsString {
        std::string Type;
        std::string Size;
        int nb;
    };
    struct kitchen {
        int id;
        bool startedTimeCounter;
        std::chrono::steady_clock::time_point begin;
        int occupiedCooks;
    };
    class Reception
    {
        public:
            Reception(float coeff, int nbCooks, int timeIngredients);
            ~Reception();
            void setPizzas(std::vector<struct infosCommandsString> listInfosCommands);
            int getIndexKitchen(void);
            int createKitchen(void);
            void manageNewCommand(std::vector<struct infosCommandsString> infosCommands);
            void checkFinishCommand(void);
            void status(void);
            void putInFile(std::string string);
        private:
            int _idCommand;
            int _idKitchen;
            std::vector<std::unique_ptr<pizzas::IPizzas>> _Commands;
            std::vector<struct plazza::kitchen> _Kitchens;
            std::unique_ptr<plazza::IPC> _ipc;
            float _multiplier;
            int _nbCooks;
            int _timeIngredients;
    };
}

#endif