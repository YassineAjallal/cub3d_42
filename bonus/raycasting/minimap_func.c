/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:45:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/01 14:50:49 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void rays_minimap(t_cub *game)
{
	t_coord	hor;
	t_coord	ver;
	t_ray	ray;
	double	horDis;
	double	verDis;
	t_coord	p;
	int		j;
	int		i;

	i = 0;
	p.x = game->p_coord.x * TILE;
	p.y = game->p_coord.y * TILE;
	ray.angle = game->player_angle - (FOV_ANGLE / 2);
	while (i < WIDTH)
	{
		ray.angle = normlize_angle(ray.angle);
		ray.down = ray.angle > 0 && ray.angle < M_PI;
		ray.up = !ray.down;
		ray.right = (ray.angle < (0.5 * M_PI)) || (ray.angle > (1.5 * M_PI));
		ray.left = !ray.right;
		j = -1;
		ver = vertical_inter(game, p, &ray);
		hor = horizontal_inter(game, p, &ray);
		verDis = calc_dis(game, ver, p);
		horDis = calc_dis(game, hor, p);
		if (horDis > verDis)
			drawline_mini(p, ver, game, rgba(255,0,0,1));
		else
			drawline_mini(p, hor, game, rgba(255,0,0,1));
		ray.angle += RAY_INC;
		i++;
	}
}