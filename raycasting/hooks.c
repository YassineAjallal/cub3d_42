/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:25:33 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/11 17:40:25 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void key_up(t_cub *game)
{
	float playercos = cos(game->player_angle) * 0.1;
	float playersin = sin(game->player_angle) * 0.1;
	float tmpx = game->p_coord.x + playercos;
	float tmpy = game->p_coord.y + playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	{
		game->p_coord.y = tmpy;
		game->p_coord.x = tmpx;

	}
}

void key_down(t_cub *game)
{
	float playercos = cos(game->player_angle) * 0.1;
	float playersin = sin(game->player_angle) * 0.1;
	float tmpx = game->p_coord.x - playercos;
	float tmpy = game->p_coord.y - playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	{
		game->p_coord.y = tmpy;
		game->p_coord.x = tmpx;

	}
}

void key_A(t_cub *game)
{
	game->player_angle -= 0.05;
	if (game->player_angle < 0)
		game->player_angle += 2 * M_PI;
	else if (game->player_angle > 2 * M_PI)
		game->player_angle -= 2 * M_PI;
}
void key_D(t_cub *game)
{
	game->player_angle += 0.05;
	if (game->player_angle < 0)
		game->player_angle += 2 * M_PI;
	else if (game->player_angle > 2 * M_PI)
		game->player_angle -= 2 * M_PI;
}

void hooks(t_cub *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		key_up(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		key_down(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		key_A(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		key_D(game);
	ray_cast(game);
}