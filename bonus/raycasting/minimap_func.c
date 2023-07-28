/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:45:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/28 20:19:52 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

float normlize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	// if (angle > 2 * M_PI)
	// 	angle -= 2 * M_PI;
	if (angle < 0)
        angle += 2 * M_PI;
	return (angle);
}

t_coord horizontal_inter(t_cub *game, float angle)
{
	t_coord result;
	angle = normlize_angle(angle);
	float xstep, ystep;
	float xintercept, yintercept;

	bool down = angle > 0 && angle < M_PI; 
	bool up = !down;
	bool right = angle < M_PI / 2 || angle > (3 * M_PI) / 2;
	bool left = !right ;

	yintercept = floorf(game->p_coord.y * TILE);
	yintercept += down ? TILE : 0;

	xintercept = (game->p_coord.x * TILE) + ((yintercept - (game->p_coord.y * TILE)) / tan(angle));
	ystep = TILE;
	ystep *= up ? -1 : 1;

	xstep = TILE / tan(angle);
	xstep *= (left && xstep > 0) ? -1 : 1;
	xstep *= (right && xstep < 0) ? -1 : 1;

	float next_H_x = xintercept;
	float next_H_y = yintercept;
	
	if (up)
		next_H_y--;
	while(next_H_x >= 0 && next_H_y >= 0 && next_H_x < 1180 && next_H_y < HEIGHT)
	{
		if ((int)floorf(next_H_y / TILE) > 13)
			break;
		if ((int)floorf(next_H_x / TILE) > ft_strlen(game->map[(int)floorf(next_H_y / TILE)]) - 1)
			break;
		if (game->map[(int)floorf(next_H_y / TILE)][(int)floorf(next_H_x / TILE)] == '1')
			break;
		next_H_x += xstep;
		next_H_y += ystep;
	}
	result.x = next_H_x;
	result.y = next_H_y;
	return (result);
}

t_coord vertical_inter(t_cub *game, float angle)
{
	t_coord result;
	angle = normlize_angle(angle);
	float xstep, ystep;
	float xintercept, yintercept;

	bool down = angle > 0 && angle < M_PI; 
	bool up = !down;
	bool right = angle < M_PI / 2 || angle > (3 * M_PI) / 2;
	bool left = !right ;


	xintercept = floorf(game->p_coord.x * TILE);
	xintercept += right ? TILE : 0;

	yintercept = (game->p_coord.y * TILE) + ((xintercept - (game->p_coord.x * TILE)) * tan(angle));

	xstep = TILE;
	xstep *= left ? -1 : 1;

	ystep = TILE * tan(angle);
	ystep *= (up && ystep > 0) ? -1 : 1;
	ystep *= (down && ystep < 0) ? -1 : 1;

	float next_V_x = xintercept;
	float next_V_y = yintercept;
	
	if (left)
		next_V_x--;
	while(next_V_x > 0 && next_V_y > 0 && next_V_x < 1180 && next_V_y < HEIGHT)
	{
		if ((int)floorf(next_V_y / TILE) > 13)
			break;
		if ((int)floorf(next_V_x / TILE) > ft_strlen(game->map[(int)floorf(next_V_y / TILE)]) - 1)
			break;
		if (game->map[(int)floorf(next_V_y / TILE)][(int)floorf(next_V_x / TILE)] == '1')
			break;
		next_V_x += xstep;
		next_V_y += ystep;
	}
	result.x = next_V_x;
	result.y = next_V_y;
	return (result);
}

void rays(t_cub *game)
{
	float angle = game->player_angle - (FOV_ANGLE / 2);
	t_coord hor, ver;
	float horDis, verDis;
	t_coord p;
	float xstep;
	float ystep;
	
	int i = 0;
	while (i < WIDTH)
	{
		p.x = game->p_coord.x * TILE;
		p.y = game->p_coord.y * TILE;
		hor = horizontal_inter(game, angle);
		horDis = calc_dis(game, hor, p);
		ver = vertical_inter(game, angle);
		verDis = calc_dis(game, ver, p);
		if (horDis < verDis)
			drawline_mini(p, hor, game, rgba(255, 25,255,1));
		else
			drawline_mini(p, ver, game, rgba(255, 25,255,1));
		angle += ray_inc;
		i++;
	}
}