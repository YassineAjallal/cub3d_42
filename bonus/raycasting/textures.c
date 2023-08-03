/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:26:47 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 15:21:49 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	*select_texture(t_cub *game, t_ray *ray, float *text_pos_x)
{
	int	*color;

	if (ray->dir == 'v')
	{
		*text_pos_x = (int)ray->wall_coord.y % TILE;
		if (ray->angle > (0.5 * M_PI) && ray->angle < (1.5 * M_PI))
			color = game->textures->color_arrayw;
		else
			color = game->textures->color_arraye;
	}
	else
	{
		*text_pos_x = (int)ray->wall_coord.x % TILE;
		if (ray->angle > 0 && ray->angle < M_PI)
			color = game->textures->color_arrays;
		else
			color = game->textures->color_arrayn;
	}
	return (color);
}

void	draw_texture(t_coord start, t_coord end, t_cub *game, t_ray *ray)
{
	float	y_incr;
	int		*color;
	float	text_pos_x;
	int		i;
	t_coord	c1;

	y_incr = (float)(ray->wall_height) / (float)game->walln->height;
	color = select_texture(game, ray, &text_pos_x);
	i = 0;
	while (i < game->walln->height)
	{
		c1.x = start.x;
		c1.y = (int)(start.y + y_incr);
		drawline(start, c1, game,
			color[(int)text_pos_x + (i * game->walln->width)]);
		start.y += y_incr;
		i++;
	}
}
