/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/07/31 21:43:32 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_texture(t_coord start, t_coord end, t_cub *game, t_ray *ray)
{
	float	y_incr;
	int		*color;
	float	text_pos_x;
	int		i;
	t_coord	c1;

	y_incr = (float)(ray->wall_height) / (float)game->wallN->height;
	i = 0;
	if (ray->dir == 'v')
	{
		text_pos_x = (int)ray->wall_coord.y % TILE;
		if (ray->angle > (0.5 * M_PI) && ray->angle < (1.5 * M_PI))
			color = game->textures->color_arrayW;
		else
			color = game->textures->color_arrayE;
	}
	else
	{
		text_pos_x = (int)ray->wall_coord.x % TILE;
		if (ray->angle > 0 && ray->angle < M_PI)
			color = game->textures->color_arrayS;
		else
			color = game->textures->color_arrayN;
	}
	while (i < game->wallN->height)
	{
		c1.x = start.x;
		c1.y = (int)(start.y + y_incr);
		drawline(start, c1, game, 
			color[(int)text_pos_x + (i * game->wallN->width)]);
		start.y += y_incr;
		i++;
	}
}

void	raycast(t_cub *game, int rayx, t_ray *ray)
{
	t_coord	start;
	t_coord	end;
	int		proj_plane;

	proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	ray->distance = ray->distance * cos(ray->angle - game->player_angle);
	ray->wall_height = (TILE / ray->distance) * proj_plane;
	start.x = rayx;
	end.x = rayx;
	start.y = (HEIGHT / 2) - (ray->wall_height / 2);
	end.y = (HEIGHT / 2) + (ray->wall_height / 2);
	draw_texture(start, end, game, ray);
}

void	rays_drawing(t_cub *game, int i, t_ray *ray, t_coord p)
{
	t_coord	hor;
	t_coord	ver;
	double	hor_dis;
	double	ver_dis;

	ver = vertical_inter(game, p, ray);
	hor = horizontal_inter(game, p, ray);
	ver_dis = calc_dis(game, ver, p);
	hor_dis = calc_dis(game, hor, p);
	if (hor_dis > ver_dis)
	{
		ray->distance = ver_dis;
		ray->wall_coord = ver;
		ray->dir = 'v';
		raycast(game, i, ray);
	}
	else
	{
		ray->distance = hor_dis;
		ray->wall_coord = hor;
		ray->dir = 'h';
		raycast(game, i, ray);
	}
}

void	rays(t_cub *game)
{
	t_ray	ray;
	t_coord	p;
	int		i;
	int		j;

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
		while (++j < HEIGHT)
		{
			if (j <= (HEIGHT / 2))
				mlx_put_pixel(game->map_img, i, j, game->ciel_color);
			else
				mlx_put_pixel(game->map_img, i, j, game->floor_color);
		}
		rays_drawing(game, i, &ray, p);
		ray.angle += RAY_INC;
		i++;
	}
}
