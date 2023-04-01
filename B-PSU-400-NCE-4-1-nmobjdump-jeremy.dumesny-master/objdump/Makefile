##
## EPITECH PROJECT, 2021
## B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
## File description:
## makefile objdump
##

name	= my_objdump

cc	= gcc

CFLAGS	+= -Wextra -Wall -Werror
CFLAGS	+= -I. -I../Shared

rm	= rm -f

srcs	= main.c my_objdump.c get_flags.c print_details.c ../used_fonction/use_elf_infos.c

OBJS	= $(srcs:.c=.o)

all: $(name)

$(name): $(OBJS)
	$(cc) $(OBJS) -o $(name) $(CFLAGS)

clean:
	$(rm) $(OBJS)

fclean: clean
	$(rm) $(name)

re: fclean all

.PHONY: all clean fclean re