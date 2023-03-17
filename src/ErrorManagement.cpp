/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "../include/ErrorManagement.hpp"

errors::ErrorManagement::ErrorManagement(const std::string &message, const std::string &where)
{
    _message = message;
    _where = where;
}

errors::ErrorManagement::~ErrorManagement() throw()
{

}

std::string const &errors::ErrorManagement::where() const
{
    return (_where);
}

const char *errors::ErrorManagement::what() const throw()
{
    return (_message.c_str());
}

errors::ReceptionError::ReceptionError(const std::string &message, const std::string &where)
                        : ErrorManagement(message, where)
{

}

errors::IpcError::IpcError(const std::string &message, const std::string &where)
        : ErrorManagement(message, where)
{

}