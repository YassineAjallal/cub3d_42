CC = cc
CFLAGS = 
NAME = cub3D
SRCS =  cub.c draw_line.c \
		hooks.c \
		init_game.c \
		raycasting.c \
		../parsing/check_valid_map.c \
		../parsing/get_map.c \
		../parsing/linkedlist.c \
		../parsing/read_map.c \
		../parsing/valid_extention.c \
		../parsing/check_map_config.c \
		../parsing/error_print.c \
		../parsing/get_next_line.c \
		../parsing/tools.c \
		../parsing/extract_config.c \

OBJS = $(SRCS:.c=.o)
GLFW = $(shell brew --prefix glfw)
MLX_FLAG = ../MLX42/build/libmlx42.a -Iinclude -lglfw -L $(GLFW)/lib/ -framework Cocoa -framework OpenGL -framework IOKit
%.o: %.c
	@$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ../libft
	@$(CC) $(CFLAGS) ../libft/libft.a $(MLX_FLAG) $^ -o $@

clean:
	@make -C ../libft clean
	@rm -f $(OBJS)

fclean: clean
	@make -C ../libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re