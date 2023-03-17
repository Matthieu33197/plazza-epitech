/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/Reception.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

plazza::Reception::Reception(float coeff, int nbCooks, int timeIngredients)
{
    _multiplier = coeff;
    _nbCooks = nbCooks;
    _timeIngredients = timeIngredients;
    _ipc = std::make_unique<plazza::IPC>();
    _idKitchen = 0;
    _idCommand = 0;
}

plazza::Reception::~Reception()
{

}

void plazza::Reception::manageNewCommand(std::vector<struct infosCommandsString> listInfosCommands)
{
    int idxKitchen = 0;
    setPizzas(listInfosCommands);
    for (int i = 0; i < _Commands[_Commands.size() - 1]->getNbPizzas(); i++) {
        try {
            idxKitchen = getIndexKitchen();
            if (idxKitchen == -1)
                throw errors::ReceptionError(
                        "The kitchen index found is incorrect",
                        "Reception::manageNewCommand");
            _Kitchens[idxKitchen].occupiedCooks++;
            _ipc->send(
                    _ipc->getIndexWithIdKitchenInput(_Kitchens[idxKitchen].id),
                    _Commands[_Commands.size() - 1]->pack(i));
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            std::exit(84);
        }
    }
}

void plazza::Reception::putInFile(std::string string)
{
    const std::string fileName = "PlazzaLog.txt";
    std::fstream processedFile(fileName.c_str());
    std::stringstream fileData;

    fileData << string << std::endl;

    fileData << processedFile.rdbuf();
    processedFile.close();

    processedFile.open(fileName.c_str(), std::fstream::out | std::fstream::trunc);
    processedFile << fileData.rdbuf();

}

void plazza::Reception::setPizzas(std::vector<struct infosCommandsString> listInfosCommands)
{
    std::string order;

    _Commands.push_back(std::make_unique<plazza::Commands>(_idCommand));
    for (int i = 0; i < listInfosCommands.size(); i++)
        _Commands[_Commands.size() - 1]->addPizza(listInfosCommands[i].Type, listInfosCommands[i].Size, listInfosCommands[i].nb);
    order = "Your order has the id: " + std::to_string(_Commands[_Commands.size() - 1]->getId()) + " (";
    for (int i = 0; i < listInfosCommands.size(); i++) {
        order += listInfosCommands[i].Type + " " + listInfosCommands[i].Size + " x" + std::to_string(listInfosCommands[i].nb);
        if (i != listInfosCommands.size() - 1)
            order += ", ";
    }
    order += "). We'll get back to you once it's finished.\n";
    std::cout << order;
    putInFile(order);
    _idCommand++;
}

int plazza::Reception::createKitchen()
{
    pid_t childPid;
    struct kitchen tmp;

    _idKitchen++;
    tmp.occupiedCooks = 0;
    tmp.id = _idKitchen;
    tmp.startedTimeCounter = false;
    tmp.begin = std::chrono::steady_clock::time_point();
    _Kitchens.push_back(tmp);
    try {
        _ipc->configIpcInput(_idKitchen);
        _ipc->configIpcOutput(_idKitchen);
        childPid = fork();
        if (childPid == -1)
            throw errors::ReceptionError("Can't create a child Process","Reception::createKitchen");
        if (childPid == 0) {
            plazza::Kitchen kitchen(_idKitchen, _multiplier, _nbCooks,
                                    _timeIngredients);
            std::exit(0);
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        std:exit(84);
    }
    return (0);
}

int plazza::Reception::getIndexKitchen()
{
    bool check = false;
    int idxLeastUsed = -1;
    int occupiedCooksAtIdx = 2 * _nbCooks;

    for (int i = 0; i < _Kitchens.size(); i++) {
        if (_Kitchens[i].occupiedCooks < occupiedCooksAtIdx) {
            idxLeastUsed = i;
            occupiedCooksAtIdx = _Kitchens[i].occupiedCooks;
            check = true;
        }
    }
    if (!check) {
        createKitchen();
        idxLeastUsed = _Kitchens.size() - 1;
    }

    return (idxLeastUsed);
}

void plazza::Reception::status(void)
{
    std::cout << std::endl;
    if (_Kitchens.size() == 0)
        std::cout << "There is no open Kitchen" << std::endl;
    for (int i = 0; i < _Kitchens.size(); i++) {
        std::cout << "Kitchen id: " << _Kitchens[i].id << std::endl;
        std::cout << "    There is " << _nbCooks << " cooks in this kitchen" << std::endl;
        if (_Kitchens[i].occupiedCooks <= _nbCooks)
                std::cout << "    There is " << _Kitchens[i].occupiedCooks << " cooks occupied" << std::endl;
        else {
            std::cout << "    There is " << _nbCooks << " cooks occupied" << std::endl;
            std::cout << "    There is " << _Kitchens[i].occupiedCooks - _nbCooks << " pizzas waiting" << std::endl;
        }
        std::cout << std::endl;
    }
}

void plazza::Reception::checkFinishCommand(void)
{
    std::string msg;
    struct pizzas::infosCommands infos = {0, pizzas::PizzaType::unknownType,
                                          pizzas::PizzaSize::unknownSize};
    std::unique_ptr <plazza::Commands> tmpCommand = std::make_unique<plazza::Commands>();

    for (int i = 0; i < _Kitchens.size(); i++) {
        for (int j = 0; j < _Kitchens[i].occupiedCooks; j++) {
            try {
                msg = _ipc->receive(
                        _ipc->getIndexWithIdKitchenOutput(_Kitchens[i].id));
            } catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
                std::exit(84);
            }
            if (!msg.empty()) {
                infos = tmpCommand->unpack(msg);
                for (int k = 0; k < _Commands.size(); k++) {
                    if (_Commands[k]->getId() == infos.idThisPizzas) {
                        _Commands[k]->removePizzas(infos.type, infos.size);
                        if (_Commands[k]->getNbPizzas() == 0) {
                            std::cout << "Reception: The command with the id:" +
                                         std::to_string(_Commands[k]->getId()) +
                                         " is now terminated !" << std::endl;
                            putInFile("Reception: The command with the id:" +
                                      std::to_string(_Commands[k]->getId()) +
                                      " is now terminated !");
                            _Commands.erase(_Commands.begin() + k);
                        }
                        break;
                    }
                }
                _Kitchens[i].occupiedCooks--;
            }
        }
        if (_Kitchens[i].occupiedCooks == 0 &&
            !_Kitchens[i].startedTimeCounter) {
            _Kitchens[i].startedTimeCounter = true;
            _Kitchens[i].begin = std::chrono::steady_clock::now();
        } else if (_Kitchens[i].occupiedCooks == 0 && _Kitchens[i].startedTimeCounter) {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(end - _Kitchens[i].begin).count() >= 5.0) {
                try {
                    _ipc->send(
                            _ipc->getIndexWithIdKitchenInput(_Kitchens[i].id),
                            "stop");
                }
                catch (const std::exception &e) {
                    std::cout << e.what() << std::endl;
                    std::exit(84);
                }
                _Kitchens.erase(_Kitchens.begin() + i);
            }
        } else {
            _Kitchens[i].startedTimeCounter = false;
            _Kitchens[i].begin = std::chrono::steady_clock::time_point();
        }
    }
}