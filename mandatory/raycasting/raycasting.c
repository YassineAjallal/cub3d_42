/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/07/31 17:34:40 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_texture(t_coord start, t_coord end, t_cub *game, int wall_height,
		double angle, t_coord hit, char dir)
{
	float	yIncr;
	int		*color;
	float	y;
	float	textPosX;
	int		i;
	int		ray_direction;
	int		posx;

	yIncr = (float)(wall_height) / (float)game->wallN->height;
	t_coord c0, c1;
	y = start.y;
	;
	i = 0;
	if (dir == 'v')
	{
		ray_direction = (int)(angle * 180 / M_PI);
		textPosX = (int)hit.y % TILE;
		if (ray_direction > 90 && ray_direction < 270)
			color = game->textures->color_arrayW;
		else
			color = game->textures->color_arrayE;
	}
	else
	{
		ray_direction = (int)(angle * 180 / M_PI);
		textPosX = (int)hit.x % TILE;
		if (ray_direction > 0 && ray_direction < 180)
			color = game->textures->color_arrayS;
		else
			color = game->textures->color_arrayN;
	}
	posx = (int)textPosX;
	while (i < game->wallN->height)
	{
		c0.x = start.x;
		c0.y = (int)y;
		c1.x = start.x;
		c1.y = (int)(y + yIncr);
		drawline(c0, c1, game, color[posx + (i * game->wallN->width)]);
		y += yIncr;
		i++;
	}
}

void	raycast(t_cub *game, int rayx, t_ray *ray, double distance,
		t_coord verHor, char type)
{
	t_coord	start;
	t_coord	end;
	int		proj_plane;
	int		wallStripHeight;

	proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	distance = distance * cos(ray->angle - game->player_angle);
	wallStripHeight = (TILE / distance) * proj_plane;
	start.x = rayx;
	end.x = rayx;
	start.y = (HEIGHT / 2) - (wallStripHeight / 2);
	end.y = (HEIGHT / 2) + (wallStripHeight / 2);
	// drawline(start, end, game, rgba(25,25,25,1));
	draw_texture(start, end, game, wallStripHeight, ray->angle, verHor, type);
}

void	rays(t_cub *game)
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
		while (++j < HEIGHT)
		{
			if (j <= (HEIGHT / 2))
				mlx_put_pixel(game->map_img, i, j, game->ciel_color);
			else
				mlx_put_pixel(game->map_img, i, j, game->floor_color);
		}
		ver = vertical_inter(game, p, &ray);
		hor = horizontal_inter(game, p, &ray);
		verDis = calc_dis(game, ver, p);
		horDis = calc_dis(game, hor, p);
		if (horDis > verDis)
			raycast(game, i, &ray, verDis, ver, 'v');
		else
			raycast(game, i, &ray, horDis, hor, 'h');
		ray.angle += RAY_INC;
		i++;
	}
}
