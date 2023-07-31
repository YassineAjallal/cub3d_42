/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:25:33 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 19:12:37 by yajallal         ###   ########.fr       */
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

void key_right(t_cub *game)
{
	float	playercos;
	float	playersin;
	float	tmpx;
	float	tmpy;

	playercos = cos(game->player_angle  - M_PI / 2) * 0.1;
	playersin = sin(game->player_angle  - M_PI / 2) * 0.1;
	tmpx = game->p_coord.x - playercos;
	tmpy = game->p_coord.y - playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	{
		game->p_coord.y = tmpy;
		game->p_coord.x = tmpx;
		rays(game);
	}
}

void key_left(t_cub *game)
{
	float	playercos;
	float	playersin;
	float	tmpx;
	float	tmpy;

	playercos = cos(game->player_angle + M_PI / 2) * 0.1;
	playersin = sin(game->player_angle + M_PI / 2) * 0.1;
	tmpx = game->p_coord.x - playercos;
	tmpy = game->p_coord.y - playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	{
		game->p_coord.y = tmpy;
		game->p_coord.x = tmpx;
		rays(game);
	}
}

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

void	open_door(t_cub *game)
{
	int i;
	float playercos = cos(game->player_angle) * 1;
	float playersin = sin(game->player_angle) * 1;
	float tmpx = game->p_coord.x + playercos;
	float tmpy = game->p_coord.y + playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] == 'D')
		game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] = '2';
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] == '2')
		game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] = 'D';
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
	if(mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		key_left(game);
	if(mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		key_right(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		key_a(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		key_d(game);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_cub *game = (t_cub *)param;
	if(keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		open_door(game);
		rays(game);
	}
}
