/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:24:52 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 20:07:15 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_coord	init_drawline(t_coord c0, t_coord c1)
{
	t_coord	s;

	if ((int)c0.x < (int)c1.x)
		s.x = 1;
	else
		s.x = -1;
	if ((int)c0.y < (int)c1.y)
		s.y = 1;
	else
		s.y = -1;
	return (s);
}

void	pixel_draw(t_coord c0, t_coord c1, t_cub *game, int color)
{
	if (c0.x >= 0 && c0.x < WIDTH && c0.y >= 0 && c0.y < HEIGHT)
		mlx_put_pixel(game->map_img, c0.x, c0.y, color);
}

void	drawline(t_coord c0, t_coord c1, t_cub *game, int color)
{
	t_coord	d;
	t_coord	s;
	int		err;
	int		err2;

	s = init_drawline(c0, c1);
	d.x = abs((int)c1.x - (int)c0.x);
	d.y = abs((int)c1.y - (int)c0.y);
	err = d.x - d.y;
	while ((int)floorf(c0.x) != (int)floorf(c1.x) 
		|| (int)floorf(c0.y) != (int)floorf(c1.y))
	{
		pixel_draw(c0, c1, game, color);
		err2 = 2 * err;
		if (err2 > -d.y)
		{
			err -= d.y;
			c0.x += s.x;
		}
		if (err2 < d.x)
		{
			err += d.x;
			c0.y += s.y;
		}
	}
}
