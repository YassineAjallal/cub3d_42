/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:26:47 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/01 12:35:47 by yajallal         ###   ########.fr       */
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
			color = game->textures->color_arrayW;
		else
			color = game->textures->color_arrayE;
	}
	else
	{
		*text_pos_x = (int)ray->wall_coord.x % TILE;
		if (ray->angle > 0 && ray->angle < M_PI)
			color = game->textures->color_arrayS;
		else
			color = game->textures->color_arrayN;
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

	y_incr = (float)(ray->wall_height) / (float)game->wallN->height;
	color = select_texture(game, ray, &text_pos_x);
	i = 0;
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
