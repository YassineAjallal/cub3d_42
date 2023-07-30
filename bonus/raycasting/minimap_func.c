/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:45:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/30 15:31:13 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

float normlize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
        angle += 2 * M_PI;
	return (angle);
}

// t_coord intersec(t_cub *game, t_coord intercept, t_coord step)
// {
// 	t_coord result;
// 	t_coord next;

// 	next.x = intercept.x;
// 	next.y = intercept.y;
// 	while(next.x > 0 && next.y > 0 && next.x < 1180 && next.y < HEIGHT)
// 	{
// 		if ((int)floorf(next.y / TILE) >= ft_strlen2d(game->map))
// 			break;
// 		if ((int)floorf(next.x / TILE) >= ft_strlen(game->map[(int)floorf(next.y / TILE)]))
// 			break;
// 		if (game->map[(int)floorf(next.y / TILE)][(int)floorf(next.x / TILE)] == '1')
// 			break;
// 		next.x += step.x;
// 		next.y += step.y;
// 	}
// 	result.x = next.x;
// 	result.y = next.y;
// 	return (result);
// }

t_coord horizontal_inter(t_cub *game, double angle, t_coord p)
{
	t_coord intercept;
	t_coord step;
	angle = normlize_angle(angle);

	bool down = angle > 0 && angle < M_PI;
	bool up = !down;
	bool right = (angle < (0.5 * M_PI)) || (angle > (1.5 * M_PI));
	bool left = !right ;

	intercept.y = (((int)p.y / TILE) * TILE);
	intercept.y += down ? TILE : 0;
	intercept.x = p.x + ((intercept.y - p.y) / tan(angle));

	step.y = TILE;
	step.y *= up ? -1 : 1;
	step.x = TILE / tan(angle);
	step.x *= (left && step.x > 0) ? -1 : 1;
	step.x *= (right && step.x < 0) ? -1 : 1;

	t_coord next;

	next.x = intercept.x;
	next.y = intercept.y;
	if (up)
		next.y--;
	t_coord result;
	while(next.x >= 0 && next.y >= 0 && next.x <= 1180 && next.y <= HEIGHT)
	{
		if ((int)floorf(next.y / TILE) >= ft_strlen2d(game->map))
			break;
		if ((int)floorf(next.x / TILE) >= ft_strlen(game->map[(int)floorf(next.y / TILE)]))
			break;
		if (game->map[(int)floorf(next.y / TILE)][(int)floorf(next.x / TILE)] == '1')
			break;
		else
		{
			next.x += step.x;
			next.y += step.y;
		}
	}
	if (up)
		next.y++;
	result.x = next.x;
	result.y = next.y;
	return (result);
}

t_coord vertical_inter(t_cub *game, double angle, t_coord p)
{
	t_coord intercept;
	t_coord step;
	angle = normlize_angle(angle);

	bool down = angle > 0 && angle < M_PI;
	bool up = !down;
	bool right = (angle < (0.5 * M_PI)) || (angle > (1.5 * M_PI));
	bool left = !right ;

	intercept.x = (((int)p.x / TILE) * TILE);
	intercept.x += right ? TILE : 0;
	intercept.y = p.y + ((intercept.x - p.x) * tan(angle));

	step.x = TILE;
	step.x *= left ? -1 : 1;

	step.y = TILE * tan(angle);
	step.y *= (up && step.y > 0) ? -1 : 1;
	step.y *= (down && step.y < 0) ? -1 : 1;
	t_coord next;

	next.x = intercept.x;
	next.y = intercept.y;
	if (left)
		next.x--;
	t_coord result;
	while(next.x >= 0 && next.y >= 0 && next.x <= 1180 && next.y <= HEIGHT)
	{
		if ((int)floorf(next.y / TILE) >= ft_strlen2d(game->map))
			break;
		if ((int)floorf(next.x / TILE) >= ft_strlen(game->map[(int)floorf(next.y / TILE)]))
			break;
		if (game->map[(int)floorf(next.y / TILE)][(int)floorf(next.x / TILE)] == '1')
			break;
		else
		{
			next.x += step.x;
			next.y += step.y;
		}
	}
	if (left)
		next.x++;
	result.x = next.x;
	result.y = next.y;
	return (result);
}

void rays_minimap(t_cub *game)
{
	double angle = game->player_angle - (FOV_ANGLE / 2);
	t_coord hor, ver;
	double horDis, verDis;
	t_coord p;

	int i = 0;
	p.x = game->p_coord.x * TILE;
	p.y = game->p_coord.y * TILE;
	while (i < WIDTH)
	{
		ver = vertical_inter(game, angle, p);
		hor = horizontal_inter(game, angle, p);
		verDis = calc_dis(game, ver, p);
		horDis = calc_dis(game, hor, p);
		if (horDis > verDis)
			drawline_mini(p, ver, game, rgba(255,0,0,1));
		else
			drawline_mini(p, hor, game, rgba(255,0,0,1));
		angle += ray_inc;
		i++;
	}
}