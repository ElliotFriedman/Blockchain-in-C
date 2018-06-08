CFLAGS = -Wall -Wextra -Werror -I libft

SRCS = main.c

OBJ = $(SRCS:.c=.o)
OBJ = $(SRCS:.c=.o)

all:
	@$(MAKE) -C libft
	gcc -Wall -Wextra -Werror main.c libft/libft.a -o block

clean:
	rm block
	make -C libft clean

fclean: clean
	make -C libft fclean
