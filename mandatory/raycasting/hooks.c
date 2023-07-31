/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:25:33 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 17:25:45 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	key_up(t_cub *game)
{
	float	playercos;
	float	playersin;
	float	tmpx;
	float	tmpy;

	playercos = cos(game->player_angle) * 0.1;
	playersin = sin(game->player_angle) * 0.1;
	tmpx = game->p_coord.x + playercos;
	tmpy = game->p_coord.y + playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	{
		game->p_coord.y = tmpy;
		game->p_coord.x = tmpx;
		rays(game);
	}
}

void	key_down(t_cub *game)
{
	float	playercos;
	float	playersin;
	float	tmpx;
	float	tmpy;

	playercos = cos(game->player_angle) * 0.1;
	playersin = sin(game->player_angle) * 0.1;
	tmpx = game->p_coord.x - playercos;
	tmpy = game->p_coord.y - playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	{
		game->p_coord.y = tmpy;
		game->p_coord.x = tmpx;
		rays(game);
	}
}

void	key_A(t_cub *game)
{
	game->player_angle -= 0.05;
	if (game->player_angle < 0)
		game->player_angle += 2 * M_PI;
	else if (game->player_angle > 2 * M_PI)
		game->player_angle -= 2 * M_PI;
	rays(game);
}

void	key_D(t_cub *game)
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
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		key_A(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		key_D(game);
}
