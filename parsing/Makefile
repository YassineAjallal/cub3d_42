CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = cub3d
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

all: $(NAME)

$(NAME): $(OBJS)
	make -C ../libft
	$(CC) $(CFLAGS) ../libft/libft.a $^ -o $@

clean:
	make -C ../libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ../libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
