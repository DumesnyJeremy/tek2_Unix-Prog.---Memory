##
## EPITECH PROJECT, 2021
## B-PSU-400-NCE-4-1-malloc-jeremy.dumesny
## File description:
## Makefile
##

NAME		=				libmy_malloc.so

MAIN_PATH	=				./
MAIN		=				alloc.c\
							free.c\
							utiles.c

# MAIN		=				malloc.c\
# 							free.c\

SRC =	$(addprefix $(MAIN_PATH), $(MAIN))\

CFLAGS  = -fPIC -Werror -Wextra -Wall -W -I.

LDFLAGS = -shared -lpthread -ggdb3

OBJ     = $(SRC:.c=.o)

CC      = gcc

RM      = rm -f

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean re fclean