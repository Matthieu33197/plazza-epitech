/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#ifndef __COMMANDS_HPP__
#define __COMMANDS_HPP__

#include <memory>
#include <vector>
#include "../include/IPizzas.hpp"
#include "../include/Kitchen.hpp"

namespace plazza
{
    class Commands : public pizzas::IPizzas {
        public:
            Commands(int id);
            Commands(){};
            ~Commands();
            int getId(void);
            pizzas::PizzaType stringToPizzaType(std::string type);
            pizzas::PizzaSize stringToPizzaSize(std::string size);
            void removePizzas(pizzas::PizzaType type, pizzas::PizzaSize size);
            int getNbPizzas(void);
            void addPizza(std::string Type, std::string Size, int nb);
            std::string pack(int i);
            struct pizzas::infosCommands unpack(std::string packedPizzas);
        private:
            int _id;
            std::vector<std::pair<pizzas::PizzaType, pizzas::PizzaSize>> _infosPizzasCommand;
    };
}

#endif
