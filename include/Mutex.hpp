/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include <mutex>

namespace plazza {

    class Mutex {
        public:
            Mutex();
            ~Mutex();
            void lock(void);
            void unlock(void);
        private:
            std::mutex _mutex;
    };
}