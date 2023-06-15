/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:24:52 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/12 11:56:34 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void drawline(t_coord c0, t_coord c1, t_cub *game, int color)
{
    int dx = abs((int)c1.x - (int)c0.x);
    int dy = abs((int)c1.y - (int)c0.y);
    int sx = (int)c0.x < (int)c1.x ? 1 : -1;
    int sy = (int)c0.y < (int)c1.y ? 1 : -1;
    int err = dx - dy;

    while (c0.x != c1.x || c0.y != c1.y)
    {
        if (c0.x >= 0 && c0.x < WIDTH && c0.y >= 0 && c0.y < HEIGHT)
            mlx_put_pixel(game->map_img, c0.x, c0.y, color);
        int err2 = 2 * err;
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