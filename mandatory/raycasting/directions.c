/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:08:44 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 20:12:14 by yajallal         ###   ########.fr       */
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

void	key_right(t_cub *game)
{
	float	playercos;
	float	playersin;
	float	tmpx;
	float	tmpy;

	playercos = cos(game->player_angle - M_PI / 2) * 0.1;
	playersin = sin(game->player_angle - M_PI / 2) * 0.1;
	tmpx = game->p_coord.x - playercos;
	tmpy = game->p_coord.y - playersin;
	if (game->map[(int)floorf(tmpy)][(int)floorf(tmpx)] != '1')
	{
		game->p_coord.y = tmpy;
		game->p_coord.x = tmpx;
		rays(game);
	}
}

void	key_left(t_cub *game)
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
