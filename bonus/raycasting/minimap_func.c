/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:45:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 18:11:24 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	cast_minimap_rays(t_cub *game, t_ray *ray, t_coord p)
{
	int		i;
	t_coord	hor;
	t_coord	ver;
	float	hor_dis;
	float	ver_dis;

	i = -1;
	while (++i < WIDTH)
	{
		ray->angle = normlize_angle(ray->angle);
		ray->down = (ray->angle > 0 && ray->angle < M_PI);
		ray->up = !ray->down;
		ray->right = ((ray->angle < (0.5 * M_PI)) || \
		(ray->angle > (1.5 * M_PI)));
		ray->left = !ray->right;
		ver = vertical_inter(game, p, ray);
		hor = horizontal_inter(game, p, ray);
		ver_dis = calc_dis(ver, p);
		hor_dis = calc_dis(hor, p);
		if (hor_dis > ver_dis)
			drawline_mini(p, ver, game, rgba(255, 0, 0, 1));
		else
			drawline_mini(p, hor, game, rgba(255, 0, 0, 1));
		ray->angle += RAY_INC;
	}
}

void	rays_minimap(t_cub *game)
{
	t_ray	ray;
	t_coord	p;
	int		i;

	i = 0;
	p.x = game->p_coord.x * TILE;
	p.y = game->p_coord.y * TILE;
	ray.angle = game->player_angle - (FOV_ANGLE / 2);
	cast_minimap_rays(game, &ray, p);
}
