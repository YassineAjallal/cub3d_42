/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:12:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/11 19:53:41 by yajallal         ###   ########.fr       */
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
		if (!game->textures)
			return (0);
		map = read_map(av[1]);
		game->map = get_map(map);
		if (!game->map)
			return (0);
		if (!check_valid_map(game->map))
			return (0);
		init_game(game);
	}
	ray_cast(game);
	mlx_loop_hook(game->mlx, hooks, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return 0;
}
