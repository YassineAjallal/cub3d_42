/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:43:26 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/15 19:48:41 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void drawline_mini(t_coord c0, t_coord c1, t_cub *game, int color)
{
    int dx = abs((int)c1.x - (int)c0.x);
    int dy = abs((int)c1.y - (int)c0.y);
    int sx = (int)c0.x < (int)c1.x ? 1 : -1;
    int sy = (int)c0.y < (int)c1.y ? 1 : -1;
    int err = dx - dy;

    while ((int)c0.x != (int)c1.x || (int)c0.y != (int)c1.y)
    {
        if (c0.x >= 0 && c0.x < 500 && c0.y >= 0 && c0.y < 500)
            mlx_put_pixel(game->minimap_img, c0.x, c0.y, color);
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
void draw_rays(t_cub *game)
{
	float angle = game->player_angle - FOV_ANGLE / 2;
    float end_angle = game->player_angle + FOV_ANGLE / 2;
	t_coord target_coord;


	while (angle < end_angle)
	{
		target_coord.x = game->p_coord.x + cos(angle) * 50;
		target_coord.y = game->p_coord.y + sin(angle) * 50;
		drawline_mini(game->p_coord, target_coord, game, 0xFF0000FF);
		angle += 0.1;
	}
}

void	draw_wall(int h, int w, t_cub *game, int color)
{
	int i = h;
	while (i < h + 10)
	{
		int j = w;
		while (j < w + 10)
		{
			if (i == h + 9 || i == h || j == w + 9 || j == w)
				mlx_put_pixel(game->minimap_img, j, i, 0x00000000);
			else
				mlx_put_pixel(game->minimap_img, j, i, color);
			j++;
		}
		i++;
	}
	
}
void	draw_maps(t_cub *game)
{
	int i = 0;
	int j;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			printf("%c", game->map[i][j]);
			if(game->map[i][j] == '1')
				draw_wall(i * 10, j * 10, game, 0x00000000);
			else if (game->map[i][j] == '0')
				draw_wall(i * 10, j * 10, game, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

void put_minimap(t_cub *game)
{
	draw_maps(game);
	draw_rays(game);
	mlx_image_to_window(game->mlx, game->minimap_img, 0, 0);
}