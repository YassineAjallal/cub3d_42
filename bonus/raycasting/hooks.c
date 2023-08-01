/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:25:33 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 20:09:13 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	key_a(t_cub *game)
{
	game->player_angle -= 0.05;
	if (game->player_angle < 0)
		game->player_angle += 2 * M_PI;
	else if (game->player_angle > 2 * M_PI)
		game->player_angle -= 2 * M_PI;
	rays(game);
}

void	key_d(t_cub *game)
{
	game->player_angle += 0.05;
	if (game->player_angle < 0)
		game->player_angle += 2 * M_PI;
	else if (game->player_angle > 2 * M_PI)
		game->player_angle -= 2 * M_PI;
	rays(game);
}

void	hooks(void *ptr)
{
	t_cub	*game;

	game = (t_cub *)ptr;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		key_up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		key_down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		key_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		key_right(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		key_a(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		key_d(game);
}
