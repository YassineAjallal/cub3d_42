/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:24:52 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 15:17:09 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	pixel_draw(t_coord c0, t_cub *game, int color)
{
	if (c0.x >= 0 && c0.x < WIDTH && c0.y >= 0 && c0.y < HEIGHT)
		mlx_put_pixel(game->map_img, c0.x, c0.y, color);
}

void	drawline(t_coord c0, t_coord c1, t_cub *game, int color)
{
	int		dx;
	int		dy;
	int		i;
	t_coord	incr;
	int		steps;

	i = 0;
	dx = c1.x - c0.x;
	dy = c1.y - c0.y;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	incr.x = dx / (float)steps;
	incr.y = dy / (float)steps;
	while (i <= steps)
	{
		pixel_draw(c0, game, color);
		c0.x += incr.x;
		c0.y += incr.y;
		i++;
	}
}
