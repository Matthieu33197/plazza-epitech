/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/IPC.hpp"
#include "../include/ErrorManagement.hpp"
#include <chrono>
#include <iostream>
#include <unistd.h>

plazza::IPC::IPC()
{
}

plazza::IPC::~IPC()
{

}

std::string plazza::IPC::receive(mqd_t fd)
{
    char msg[20];
    std::string result;

    if (mq_receive(fd, msg, 20, NULL) == -1) {
        result.clear();
        return (result);
    }
    result.assign(msg);

    return (result);
}

int plazza::IPC::send(mqd_t fd, std::string msg)
{
    if (mq_send(fd, msg.c_str(), msg.length() + 1, 0) == -1)
        throw errors::IpcError("Can't send the message", "IPC::send");

    return (0);
}

int plazza::IPC::configIpcInput(int idKitchen)
{
    mqd_t fd = 0;
    struct mq_attr attr = {0, 0, 0, 0};
    int flags = 0;
    std::string nameIPC("/ToKitchen " + std::to_string(idKitchen));

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 20;
    flags = O_RDWR | O_CREAT;
    fd = mq_open(nameIPC.c_str(), flags, 0666, &attr);
    if (fd == -1)
        throw errors::IpcError("Can't open a Message Queue INPUT", "IPC::configIpcInput");
    _input.push_back(std::make_pair(idKitchen, fd));
    return (0);
}

int plazza::IPC::configIpcOutput(int idKitchen)
{
    mqd_t fd = 0;
    struct mq_attr attr = {0, 0, 0, 0};;
    int flags = 0;
    std::string nameIPC("/ToReception " + std::to_string(idKitchen));

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 20;
    mq_unlink(nameIPC.c_str());
    flags = O_RDWR | O_CREAT | O_NONBLOCK;
    fd = mq_open(nameIPC.c_str(), flags, 0666, &attr);
    if (fd == -1)
        throw errors::IpcError("Can't open a Message Queue OUTPUT", "IPC::configIpcOutput");
    _output.push_back(std::make_pair(idKitchen, fd));
    return (0);
}

mqd_t plazza::IPC::getIndexWithIdKitchenInput(int idKitchen)
{
    if (_input.size() != 0) {
        for (int i = 0; i < _input.size(); i++) {
            if (_input[i].first == idKitchen)
                return (_input[i].second);
        }
    }
    throw errors::IpcError("Can't find the Kitchen index input", "IPC::getIndexWithIdKitchenInput");

}

mqd_t plazza::IPC::getIndexWithIdKitchenOutput(int idKitchen)
{
    if (_output.size() != 0) {
        for (int i = 0; i < _output.size(); i++) {
            if (_output[i].first == idKitchen)
                return (_output[i].second);
        }
    }
    throw errors::IpcError("Can't find the Kitchen index output", "IPC::getIndexWithIdKitchenOutput");

}