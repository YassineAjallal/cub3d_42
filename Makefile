CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME_MANDA = cub3D
NAME_BONUS = cub3D_bonus
SRCS_MANDA =	mandatory/parsing/check_map_config.c \
				mandatory/parsing/check_map_config_tool.c \
				mandatory/parsing/error_print.c \
				mandatory/parsing/get_map.c \
				mandatory/parsing/linkedlist.c \
				mandatory/parsing/tools.c \
				mandatory/raycasting/hooks.c \
				mandatory/parsing/check_valid_map.c \
				mandatory/parsing/check_valid_map_tool.c \
				mandatory/parsing/extract_config.c \
				mandatory/parsing/get_next_line.c \
				mandatory/parsing/read_map.c \
				mandatory/parsing/valid_extention.c \
				mandatory/raycasting/cub.c \
				mandatory/raycasting/draw_line.c \
				mandatory/raycasting/init_game.c \
				mandatory/raycasting/raycasting.c \
				mandatory/raycasting/directions.c \
				mandatory/raycasting/raycast_algo.c  \
				mandatory/raycasting/raycast_tools.c  \
				mandatory/raycasting/textures.c  \
				mandatory/raycasting/free_func.c  \

SRCS_BONUS = 	bonus/parsing/check_map_config.c \
				bonus/parsing/check_map_config_tool.c \
				bonus/parsing/error_print.c \
				bonus/parsing/get_map.c \
				bonus/parsing/linkedlist.c \
				bonus/parsing/tools.c \
				bonus/raycasting/hooks.c \
				bonus/parsing/check_valid_map.c \
				bonus/parsing/check_valid_map_tool.c \
				bonus/parsing/extract_config.c \
				bonus/parsing/get_next_line.c \
				bonus/parsing/read_map.c \
				bonus/parsing/valid_extention.c \
				bonus/raycasting/cub.c \
				bonus/raycasting/draw_line.c \
				bonus/raycasting/hooks.c \
				bonus/raycasting/init_game.c \
				bonus/raycasting/minimap.c \
				bonus/raycasting/raycasting.c \
				bonus/raycasting/raycast_algo.c \
				bonus/raycasting/minimap_func.c \
				bonus/raycasting/raycast_tools.c  \
				bonus/raycasting/textures.c  \
				bonus/raycasting/directions.c \
				bonus/raycasting/free_func.c  \


OBJS_MANDA = $(SRCS_MANDA:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
GLFW = $(shell brew --prefix glfw)
MLX_FLAG = MLX42/build/libmlx42.a -Iinclude -lglfw -L $(GLFW)/lib/ -framework Cocoa -framework OpenGL -framework IOKit

%.o: %.c
	@$(CC)  -c $< -o $@

all: $(NAME_MANDA) $(NAME_BONUS)

mandatory: $(NAME_MANDA)

bonus: $(NAME_BONUS)

$(NAME_MANDA): $(OBJS_MANDA)
	@make -C libft
	@$(CC) $(CFLAGS) libft/libft.a $(MLX_FLAG) $^ -o $@

$(NAME_BONUS): $(OBJS_BONUS)
	@make -C libft
	@$(CC) $(CFLAGS) libft/libft.a $(MLX_FLAG) $^ -o $@

clean:
	@make -C libft clean
	@rm -f $(OBJS_MANDA)
	@rm -f $(OBJS_BONUS)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME_MANDA)
	@rm -f $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean all re
