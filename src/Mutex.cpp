/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/Mutex.hpp"

plazza::Mutex::Mutex()
{

}

plazza::Mutex::~Mutex()
{

}

void plazza::Mutex::lock()
{
    _mutex.lock();
}

void plazza::Mutex::unlock()
{
    _mutex.unlock();
}