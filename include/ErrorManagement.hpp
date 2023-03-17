/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include <exception>
#include <string>

namespace errors {
    class ErrorManagement : public std::exception {
        public:
            ErrorManagement(std::string const &message, std::string const &where = "Unknown");
            virtual ~ErrorManagement() throw();
            std::string const &where() const;
            const char* what() const throw();
        private:
            std::string _message;
            std::string	_where;
    };

    class ReceptionError : public ErrorManagement {
        public:
            ReceptionError(const std::string &message = "Unknown",
                               const std::string &where = "Unknown");
    };
    class IpcError : public ErrorManagement {
    public:
        IpcError(const std::string &message = "Unknown",
                       const std::string &where = "Unknown");
    };
}