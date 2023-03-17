/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/Core.hpp"
#include <string.h>
#include <signal.h>

plazza::Core::Core(float multiplier, int nbCooks, int timeIngredients)
{
    _multiplier = multiplier;
    _nbCooks = nbCooks;
    _timeIngredients = timeIngredients;
    _reception = std::make_unique<plazza::Reception>(_multiplier, _nbCooks, _timeIngredients);
    Loop();
}

plazza::Core::~Core()
{

}

std::string plazza::Core::getCommand()
{
    std::string cmd;
    fd_set fds;
    struct timeval tv {0, 10};
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    int selectfd = 0;

    selectfd = select(0 + 1, &fds, NULL, NULL, &tv);
    if (selectfd > 0) {
        getline(std::cin, cmd);
        return (cmd);
    }
    else {
        _reception->checkFinishCommand();
        cmd.clear();
        return (cmd);
    }
}

void plazza::Core::Loop()
{
    std::string cmd;
    plazza::Parser parse;
    std::vector<std::string> tmpCommands;

    while (strcasecmp(cmd.c_str(), "quit") != 0) {
        cmd = getCommand();
        if (!cmd.empty() && strcasecmp(cmd.c_str(), "quit") != 0) {
            if (strcasecmp(cmd.c_str(), "status") == 0) {
                _reception->status();
            } else if (strcasecmp(cmd.c_str(), "clear") == 0)
                std::system("clear");
            else {
                _listCommand = parse.parseCommand(cmd);
                if (_listCommand.size() == 0)
                    std::cout << "There is an error in your command"
                              << std::endl;
                else {
                    _reception->manageNewCommand(_listCommand);
                }
            }
        }
    }
}