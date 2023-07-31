/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:14:19 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 13:01:15 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double calc_dis(t_cub *game, t_coord hit, t_coord p)
{
	double dis;
	dis = sqrt(pow(hit.x - p.x, 2) + pow(hit.y - p.y, 2));
	return (dis);
}

float normlize_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}
t_coord intersec(t_cub *game, t_ray *ray, char type)
{
	t_coord result;
	t_coord next;

	next.x = ray->intercept.x;
	next.y = ray->intercept.y;
	if (type == 'v' && ray->left)
		next.x--;
	if (type == 'h' && ray->up)
		next.y--;
	while(next.x >= 0 && next.y >= 0 && next.x <= TILE * game->large_length && next.y <= TILE * game->map_len)
	{
		if ((int)floorf(next.y / TILE) >= ft_strlen2d(game->map))
			break;
		if ((int)floorf(next.x / TILE) >= ft_strlen(game->map[(int)floorf(next.y / TILE)]))
			break;
		if (game->map[(int)floorf(next.y / TILE)][(int)floorf(next.x / TILE)] == '1')
			break;
		next.x += ray->step.x;
		next.y += ray->step.y;
	}
	if (type == 'v' && ray->left)
		next.x++;
	if (type == 'h' && ray->up)
		next.y++;
	result.x = next.x;
	result.y = next.y;
	return (result);
}

t_coord horizontal_inter(t_cub *game, t_coord p, t_ray *ray)
{
	t_coord result;

	ray->intercept.y = ((int)p.y / TILE) * TILE;
	if (ray->down)
		ray->intercept.y += TILE;
	ray->intercept.x = p.x + ((ray->intercept.y - p.y) / tan(ray->angle));
	ray->step.y = TILE;
	if (ray->up)
		ray->step.y *= -1;
	ray->step.x = TILE / tan(ray->angle);
	if (ray->left && ray->step.x > 0)
		ray->step.x *= -1;
	if (ray->right && ray->step.x < 0)
		ray->step.x *= -1;
	result = intersec(game, ray, 'h');
	return (result);
}

t_coord vertical_inter(t_cub *game, t_coord p, t_ray *ray)
{
	t_coord result;

	ray->intercept.x = ((int)p.x / TILE) * TILE;
	if (ray->right)
		ray->intercept.x += TILE;
	ray->intercept.y = p.y + ((ray->intercept.x - p.x) * tan(ray->angle));
	ray->step.x = TILE;
	if (ray->left)
		ray->step.x *= -1;
	ray->step.y = TILE * tan(ray->angle);
	if (ray->up && ray->step.y > 0)
		ray->step.y *= -1;
	if (ray->down && ray->step.y < 0)
		ray->step.y *= -1;
	result = intersec(game, ray, 'v');
	return (result);
}


