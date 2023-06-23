/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:12:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/22 16:30:57 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

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
		game->dda = malloc(sizeof(t_dda));
		if (!game->textures || !game->dda)
			return (0);
		map = read_map(av[1]);
		game->map = get_map(map, game);
		if (!game->map)
			error_print("map not found\n");
		game->textures_img = extract_textures(map);	
		if (!check_valid_map(game->map))
			error_print("map not valid \n");
		init_game(game);
	}
	game->dda->dirx = -1;
	game->dda->diry = 0;
	game->dda->planex = 0;
	game->dda->planey = 0.66;
	ray_cast(game);
	mlx_loop_hook(game->mlx, hooks, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return 0;
}
