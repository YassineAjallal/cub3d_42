/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:12:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/16 11:09:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	move_mouse( double x, double y, void *ptr)
{
	t_cub *game = (t_cub *)ptr;
	int xi;
	int yi;
	mlx_get_mouse_pos(game->mlx,&xi,&yi);
	if(xi > game->mouse_x)
	{
		game->player_angle += 0.08;
		if (game->player_angle < 0)
			game->player_angle += 2 * M_PI;
		else if (game->player_angle > 2 * M_PI)
			game->player_angle -= 2 * M_PI;
		game->mouse_x = x;
	}
	else if (xi < game->mouse_x)
	{
		game->player_angle -= 0.08;
			if (game->player_angle < 0)
			game->player_angle += 2 * M_PI;
		else if (game->player_angle > 2 * M_PI)
			game->player_angle -= 2 * M_PI;
		game->mouse_x = x;
	}
}

int main(int ac, char **av)
{
	t_cub *game;
	t_map *map;
	if (ac != 2)
		error_print("Bad Usage\n");
	else
	{
		game = malloc(sizeof(t_cub));
		map = malloc(sizeof(t_map));
		if (!game || !map)
			return (0);
		game->textures = malloc(sizeof(t_textures));
		if (!game->textures)
			return (0);
		map = read_map(av[1]);
		game->map = get_map(map, game);
		game->textures_img = extract_textures(map);
		if (!game->map)
			return (0);
		if (!check_valid_map(game->map))
			error_print("map not valid \n");
		init_game(game);
	}
	ray_cast(game);
	put_minimap(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(game->mlx,&game->mouse_x,&game->mouse_y);
	mlx_loop_hook(game->mlx, hooks, game);
	mlx_key_hook(game->mlx, my_keyhook, game);
	mlx_cursor_hook(game->mlx, move_mouse, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return 0;
}
