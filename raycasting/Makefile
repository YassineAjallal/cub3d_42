CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = cub
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make -C ../libft
	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	make -C ../libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ../libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re