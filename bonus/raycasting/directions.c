/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:08:44 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/01 14:45:58 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	key_up(t_cub *game)
{
	float	playercos;
	float	playersin;
	t_coord	tmp;
	float	plac;
	float	places;

	playercos = cos(game->player_angle) * 0.1;
	playersin = sin(game->player_angle) * 0.1;
	plac = cos(game->player_angle) * 0.3;
	places = sin(game->player_angle) * 0.3;
	tmp.x = game->p_coord.x + plac;
	tmp.y = game->p_coord.y + places;
	if (game->map[(int)floorf(tmp.y)][(int)floorf(tmp.x)] != '1' \
	&& game->map[(int)game->p_coord.y][(int)floorf(tmp.x)] != '1' \
	&& game->map[(int)floorf(tmp.y)][(int)game->p_coord.x] != '1')
	{
		game->p_coord.y += playersin;
		game->p_coord.x += playercos;
		rays(game);
	}
}

void	key_down(t_cub *game)
{
	float	playercos;
	float	playersin;
	t_coord	tmp;
	float	plac;
	float	places;

	playercos = cos(game->player_angle) * 0.1;
	playersin = sin(game->player_angle) * 0.1;
	plac = cos(game->player_angle) * 0.3;
	places = sin(game->player_angle) * 0.3;
	tmp.x = game->p_coord.x - plac;
	tmp.y = game->p_coord.y - places;
	if (game->map[(int)floorf(tmp.y)][(int)floorf(tmp.x)] != '1' \
	&& game->map[(int)game->p_coord.y][(int)floorf(tmp.x)] != '1' \
	&& game->map[(int)floorf(tmp.y)][(int)game->p_coord.x] != '1')
	{
		game->p_coord.y -= playersin;
		game->p_coord.x -= playercos;
		rays(game);
	}
}

void	key_right(t_cub *game)
{
	float	playercos;
	float	playersin;
	t_coord	tmp;
	float	plac;
	float	places;

	playercos = cos(game->player_angle - M_PI / 2) * 0.1;
	playersin = sin(game->player_angle - M_PI / 2) * 0.1;
	plac = cos(game->player_angle - M_PI / 2) * 0.3;
	places = sin(game->player_angle - M_PI / 2) * 0.3;
	tmp.x = game->p_coord.x - plac;
	tmp.y = game->p_coord.y - places;
	if (game->map[(int)floorf(tmp.y)][(int)floorf(tmp.x)] != '1' \
	&& game->map[(int)game->p_coord.y][(int)floorf(tmp.x)] != '1' \
	&& game->map[(int)floorf(tmp.y)][(int)game->p_coord.x] != '1')
	{
		game->p_coord.y -= playersin;
		game->p_coord.x -= playercos;
		rays(game);
	}
}

void	key_left(t_cub *game)
{
	float	playercos;
	float	playersin;
	t_coord	tmp;
	float	plac;
	float	places;

	playercos = cos(game->player_angle + M_PI / 2) * 0.1;
	playersin = sin(game->player_angle + M_PI / 2) * 0.1;
	plac = cos(game->player_angle + M_PI / 2) * 0.3;
	places = sin(game->player_angle + M_PI / 2) * 0.3;
	tmp.x = game->p_coord.x - playercos;
	tmp.y = game->p_coord.y - playersin;
	if (game->map[(int)floorf(tmp.y)][(int)floorf(tmp.x)] != '1' \
	&& game->map[(int)game->p_coord.y][(int)floorf(tmp.x)] != '1' \
	&& game->map[(int)floorf(tmp.y)][(int)game->p_coord.x] != '1')
	{
		game->p_coord.y -= playersin;
		game->p_coord.x -= playercos;
		rays(game);
	}
}
