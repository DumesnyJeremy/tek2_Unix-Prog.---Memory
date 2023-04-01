##
## EPITECH PROJECT, 2021
## B-PSU-400-NCE-4-1-nmobjdump-jeremy.dumesny
## File description:
## makefile
##

my_nm		= my_nm
my_objdump	= my_objdump

make	= make -C
cp		= cp -f
rm		= rm -f

nm		= nm
objdump	= objdump

all: nm objdump

clean:
	$(make) $(nm) clean
	$(make) $(objdump) clean

fclean:
	$(make) $(nm) fclean
	$(make) $(objdump) fclean
	$(rm) $(my_nm)
	$(rm) $(my_objdump)

re: fclean all

nm:
	$(make) $(nm)
	$(cp) $(nm)/$(my_nm) $(my_nm)

objdump:
	$(make) $(objdump)
	$(cp) $(objdump)/$(my_objdump) $(my_objdump)

.PHONY: all clean fclean re nm objdump