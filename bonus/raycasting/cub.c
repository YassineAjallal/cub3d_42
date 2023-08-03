/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:12:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 19:33:20 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	error_checker(char **av, t_cub *game, t_map *map)
{
	map = read_map(av[1]);
	game->map = get_map(map, game);
	if (!game->map)
	{
		free(game->textures);
		free_list(map);
		free(game);
		error_print("map not found\n");
	}
	game->large_length = get_large_line(game);
	game->textures_img = extract_textures(map);
	if (!check_valid_map(game->map))
	{
		free(game->textures);
		ft_free2d(game->textures_img);
		ft_free2d(game->map);
		free(game);
		error_print("map not valid \n");
	}
}

void	move_mouse( double x, double y, void *ptr)
{
	t_cub	*game;
	int		xi;
	int		yi;

	game = (t_cub *)ptr;
	mlx_get_mouse_pos(game->mlx, &xi, &yi);
	if (xi > game->mouse_x)
	{
		game->player_angle += 0.1;
		if (game->player_angle < 0)
			game->player_angle += 2 * M_PI;
		else if (game->player_angle > 2 * M_PI)
			game->player_angle -= 2 * M_PI;
		game->mouse_x = xi;
	}
	else if (xi < game->mouse_x)
	{
		game->player_angle -= 0.1;
		if (game->player_angle < 0)
			game->player_angle += 2 * M_PI;
		else if (game->player_angle > 2 * M_PI)
			game->player_angle -= 2 * M_PI;
		game->mouse_x = xi;
	}
}

void	ray_cast(void *pt)
{
	t_cub	*game;

	game = (t_cub *)pt;
	rays(game);
}

int	final_game(char **av, t_cub *game, t_map *map)
{
	error_checker(av, game, map);
	if (!init_game(game))
	{
		free(game->textures);
		ft_free2d(game->map);
		free(game);
		return (0);
	}
	rays(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(game->mlx, &game->mouse_x, &game->mouse_y);
	mlx_loop_hook(game->mlx, hooks, game);
	mlx_cursor_hook(game->mlx, move_mouse, game);
	mlx_loop_hook(game->mlx, ray_cast, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_colors(game);
	free_texturs(game);
	free(game->textures);
	ft_free2d(game->map);
	free(game);
	return (1);
}

int	main(int ac, char **av)
{
	t_cub	*game;
	t_map	*map;

	if (ac != 2)
		error_print("Bad Usage\n");
	else
	{
		game = malloc(sizeof(t_cub));
		if (!game)
			return (0);
		map = malloc(sizeof(t_map));
		if (!map)
			return (free(game), 0);
		game->textures = malloc(sizeof(t_textures));
		if (!game->textures)
			return (free(map), free(game), 0);
		if (!final_game(av, game, map))
			return (0);
	}
	return (0);
}
