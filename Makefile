##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CXX		= 	g++

SRC     =	src/main.cpp				\
			src/Core.cpp				\
			src/Parser.cpp				\
			src/Commands.cpp			\
			src/Kitchen.cpp				\
			src/Reception.cpp			\
			src/Cooks.cpp				\
			src/IPC.cpp					\
			src/Mutex.cpp				\
			src/Ingredients.cpp			\
			src/ErrorManagement.cpp		\

OBJ	=	$(SRC:.cpp=.o)

CFLAGS = -pthread -lrt

NAME 	= 	plazza

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

re:	fclean all

fclean: clean
	rm -rf $(NAME)

.PHONY: all clean fclean re