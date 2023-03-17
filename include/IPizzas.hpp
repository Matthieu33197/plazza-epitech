/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#ifndef __IPIZZA__
#define __IPIZZA__

namespace pizzas
{
    enum PizzaType {
        unknownType = 0,
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };
    enum PizzaSize {
        unknownSize = 0,
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
    struct infosCommands {
        int idThisPizzas;
        pizzas::PizzaType type;
        pizzas::PizzaSize size;
    };
    class IPizzas
    {
        public:
            virtual ~IPizzas() = default;
            virtual int getNbPizzas(void) = 0;
            virtual int getId(void) = 0;
            virtual void addPizza(std::string Type, std::string Size, int nb) = 0;
            virtual void removePizzas(pizzas::PizzaType type, pizzas::PizzaSize size) = 0;
            virtual std::string pack(int i) = 0;
            virtual struct infosCommands unpack(std::string packedPizzas) = 0;

    private:

    };
}

#endif