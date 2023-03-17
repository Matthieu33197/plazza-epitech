/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#ifndef __IPC_HPP__
#define __IPC_HPP__

#include <mqueue.h>
#include <vector>
#include <string>

namespace plazza {
    class IPC {
        public:
            IPC();
            ~IPC();
            std::string receive(mqd_t fd);
            int send(mqd_t fd, std::string msg);
            int configIpcInput(int idKitchen);
            int configIpcOutput(int idKitchen);
            mqd_t getIndexWithIdKitchenInput(int idKitchen);
            mqd_t getIndexWithIdKitchenOutput(int idKitchen);
        private:
            std::vector<std::pair<int, mqd_t>> _input;
            std::vector<std::pair<int, mqd_t>> _output;


    };
}

#endif