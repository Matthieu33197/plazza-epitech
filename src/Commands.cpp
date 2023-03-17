/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/Commands.hpp"
#include <string>
#include <iostream>

plazza::Commands::Commands(int id)
{
    _id = id;
}

plazza::Commands::~Commands()
{

}

int plazza::Commands::getId()
{
    return (_id);
}

int plazza::Commands::getNbPizzas()
{
    return (_infosPizzasCommand.size());
}

pizzas::PizzaType plazza::Commands::stringToPizzaType(std::string type)
{
    if (type.compare("regina") == 0)
        return (pizzas::PizzaType::Regina);
    else if (type.compare("margarita") == 0)
        return (pizzas::PizzaType::Margarita);
    else if (type.compare("americana") == 0)
        return (pizzas::PizzaType::Americana);
    else if (type.compare("fantasia") == 0)
        return (pizzas::PizzaType::Fantasia);

    return (pizzas::PizzaType::unknownType);
}

pizzas::PizzaSize plazza::Commands::stringToPizzaSize(std::string size)
{
    if (size.compare("s") == 0)
        return (pizzas::PizzaSize::S);
    else if (size.compare("m") == 0)
        return (pizzas::PizzaSize::M);
    else if (size.compare("l") == 0)
        return (pizzas::PizzaSize::L);
    else if (size.compare("xl") == 0)
        return (pizzas::PizzaSize::XL);
    else if (size.compare("xxl") == 0)
        return (pizzas::PizzaSize::XXL);

    return (pizzas::PizzaSize::unknownSize);

}

void plazza::Commands::addPizza(std::string Type, std::string Size, int nb)
{
    pizzas::PizzaType typeEnum;
    pizzas::PizzaSize sizeEnum;

    typeEnum = stringToPizzaType(Type);
    sizeEnum = stringToPizzaSize(Size);

    for (int i = 0; i < nb; i++)
        _infosPizzasCommand.push_back(std::make_pair(typeEnum, sizeEnum));
}

std::string plazza::Commands::pack(int i)
{
    std::string result;

    result = std::to_string(_id) + ";" + std::to_string(_infosPizzasCommand[i].first) + ";" + std::to_string(_infosPizzasCommand[i].second);

    return (result);
}

struct pizzas::infosCommands plazza::Commands::unpack(std::string packedPizzas)
{
    struct pizzas::infosCommands result;
    std::string tmp;
    int end = packedPizzas.find(";");
    int start = 0;
    int count = 0;
    bool error = false;

    result.size = pizzas::PizzaSize::unknownSize;
    result.type = pizzas::PizzaType::unknownType;
    result.idThisPizzas = -1;
    while (end != -1) {
        tmp = packedPizzas.substr(start, end - start);
        if (count == 0)
            result.idThisPizzas = atoi(tmp.c_str());
        else if (count == 1) {
            if (tmp.compare("1") == 0)
                result.type = pizzas::PizzaType::Regina;
            else if (tmp.compare("2") == 0)
                result.type = pizzas::PizzaType::Margarita;
            else if (tmp.compare("4") == 0)
                result.type = pizzas::PizzaType::Americana;
            else if (tmp.compare("8") == 0)
                result.type = pizzas::PizzaType::Fantasia;
            else
                error = true;
        }
        start = end + 1;
        end = packedPizzas.find(";", start);
        if (start > end && end != -1)
            return (result);
        tmp.clear();
        count++;
    }
    tmp = packedPizzas.substr(start, packedPizzas.size());
    if (tmp.compare("1") == 0)
        result.size = pizzas::PizzaSize::S;
    else if (tmp.compare("2") == 0)
        result.size = pizzas::PizzaSize::M;
    else if (tmp.compare("4") == 0)
        result.size = pizzas::PizzaSize::L;
    else if (tmp.compare("8") == 0)
        result.size = pizzas::PizzaSize::XL;
    else if (tmp.compare("16") == 0)
        result.size = pizzas::PizzaSize::XXL;
    else
        error = true;
    return (result);
}

void plazza::Commands::removePizzas(pizzas::PizzaType type, pizzas::PizzaSize size)
{
    for (int i = 0; i < _infosPizzasCommand.size(); i++) {
        if (_infosPizzasCommand[i].first == type && _infosPizzasCommand[i].second == size) {
            _infosPizzasCommand.erase(_infosPizzasCommand.begin() + i);
            break;
        }
    }
}