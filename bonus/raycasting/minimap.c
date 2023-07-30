/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:43:26 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/30 15:24:24 by yajallal         ###   ########.fr       */
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
        if (c0.x >= 0 && c0.x < 1180 && c0.y >= 0 && c0.y < 760)
        	mlx_put_pixel(game->map_img, c0.x * SCALE_MINIMAP, c0.y * SCALE_MINIMAP, color);
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

double calc_dis(t_cub *game, t_coord hit, t_coord p)
{
	double dis;
	dis = sqrt((hit.x - p.x) * (hit.x - p.x) + ((hit.y - p.y) * (hit.y - p.y)));
	return (dis);
}


void	draw_wall(int h, int w, t_cub *game, int color)
{
	int i = h;
	while (i <= h + TILE)
	{
		int j = w;
		while (j <= w + TILE)
		{
			// if (j == w || j == w + TILE || i == h || i == h + TILE)
			// 	mlx_put_pixel(game->map_img, i * SCALE_MINIMAP, j * SCALE_MINIMAP, rgba(20,20,20,1));
			// else
				mlx_put_pixel(game->map_img, i * SCALE_MINIMAP, j * SCALE_MINIMAP, color);
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
			if(game->map[i][j] == '1')
				draw_wall(j * TILE, i * TILE, game, rgba(255, 255, 255, 1));
			 if (game->map[i][j] == '0' || game->map[i][j] == ' ' || ft_strchr("ESNW", game->map[i][j]))
				draw_wall(j * TILE, i * TILE, game, rgba(0, 0, 0, 1));
			j++;
		}
		i++;
	}
}

void put_minimap(t_cub *game)
{
	draw_maps(game);
	rays_minimap(game);
}
