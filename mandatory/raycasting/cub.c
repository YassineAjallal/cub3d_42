/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:12:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 13:17:14 by yajallal         ###   ########.fr       */
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
		game->map = get_map(map, game);
		if (!game->map)
			error_print("map not found\n");
		game->large_length = get_large_line(game);
		// printf("%d\n",game->large_length);
		// exit(0);
		game->textures_img = extract_textures(map);
		if (!check_valid_map(game->map))
			error_print("map not valid \n");
		init_game(game);
		rays(game);
		mlx_loop_hook(game->mlx, hooks, game);
		mlx_loop(game->mlx);
		mlx_terminate(game->mlx);
	}
	return 0;
}
