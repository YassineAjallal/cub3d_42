/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:14:19 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 15:16:38 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	intersec_tool(t_cub *game, t_coord *next, t_ray *ray)
{
	while (next->x >= 0 && next->y >= 0 && next->x <= TILE * game->large_length
		&& next->y <= TILE * game->map_len)
	{
		if ((int)floorf(next->y / TILE) >= ft_strlen2d(game->map))
			break ;
		if ((int)floorf(next->x / TILE) >= \
			ft_strlen(game->map[(int)floorf(next->y / TILE)]))
			break ;
		if (game->map[(int)floorf(next->y / TILE)]
			[(int)floorf(next->x / TILE)] == '1')
			break ;
		next->x += ray->step.x;
		next->y += ray->step.y;
	}
}

t_coord	intersec(t_cub *game, t_ray *ray, char type)
{
	t_coord	result;
	t_coord	next;

	next.x = ray->intercept.x;
	next.y = ray->intercept.y;
	if (type == 'v' && ray->left)
		next.x--;
	if (type == 'h' && ray->up)
		next.y--;
	intersec_tool(game, &next, ray);
	if (type == 'v' && ray->left)
		next.x++;
	if (type == 'h' && ray->up)
		next.y++;
	result.x = next.x;
	result.y = next.y;
	return (result);
}

t_coord	horizontal_inter(t_cub *game, t_coord p, t_ray *ray)
{
	t_coord	result;

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

t_coord	vertical_inter(t_cub *game, t_coord p, t_ray *ray)
{
	t_coord	result;

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
