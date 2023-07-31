/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:24:52 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 17:33:28 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	drawline(t_coord c0, t_coord c1, t_cub *game, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;

	dx = abs((int)c1.x - (int)c0.x);
	dy = abs((int)c1.y - (int)c0.y);
	sx = (int)c0.x < (int)c1.x ? 1 : -1;
	sy = (int)c0.y < (int)c1.y ? 1 : -1;
	err = dx - dy;
	while ((int)floorf(c0.x) != (int)floorf(c1.x)
		|| (int)floorf(c0.y) != (int)floorf(c1.y))
	{
		if (c0.x >= 0 && c0.x < WIDTH && c0.y >= 0 && c0.y < HEIGHT)
			mlx_put_pixel(game->map_img, c0.x, c0.y, color);
		err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			c0.x += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			c0.y += sy;
		}
	}
}
