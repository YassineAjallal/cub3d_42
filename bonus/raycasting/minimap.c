/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:43:26 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/17 18:33:15 by yajallal         ###   ########.fr       */
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
		if (game->map[(int)c0.y / 10][(int)c0.x / 10] == '1' || game->map[(int)c0.y / 10][(int)c0.x / 10] == 'D')
			break;
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
	// int dx;
    // int dy;
    // float len;
    // float x_inc;
    // float y_inc;
    // int i;

    // i = 0;
    // dx = abs((int)c1.x - (int)c0.x);
    // dy = abs((int)c1.y - (int)c0.y);
    // if (dy > dx)
    //     len = dy;
    // else
    //     len = dx;
    // x_inc = dx / len;
    // y_inc = dy / len;
    // while(i < len)
    // {
	// 	if (game->map[(int)c0.y / 10][(int)c0.x / 10] == '1' || game->map[(int)c0.y / 10][(int)c0.x / 10] == 'D')
	// 		break;
    //     if (c0.x >= 0 && c0.x < 500 && c0.y >= 0 && c0.y < 500)
    //         mlx_put_pixel(game->minimap_img, c0.x, c0.y, color);
    //     c0.x += x_inc;
    //     c0.y += y_inc;
    //     i++;
    // }
}
// void drawline(t_coord c0, t_coord c1, t_cub *game, int color)
// {
//     int dx;
//     int dy;
//     float len;
//     float x_inc;
//     float y_inc;
//     int i;

//     i = 0;
//     dx = abs((int)c1.x - (int)c0.x);
//     dy = abs((int)c1.y - (int)c0.y);
//     if (dy > dx)
//         len = dy;
//     else
//         len = dx;
//     x_inc = dx / len;
//     y_inc = dy / len;
//     while(i < len)
//     {
//         if (c0.x >= 0 && c0.x < WIDTH && c0.y >= 0 && c0.y < HEIGHT)
//             mlx_put_pixel(game->map_img, c0.x, c0.y, color);
//         c0.x += x_inc;
//         c0.y += y_inc;
//         i++;
//     }
// }
void draw_rays(t_cub *game)
{
	float angle = game->player_angle - FOV_ANGLE / 2;
    float end_angle = game->player_angle + FOV_ANGLE / 2;
	t_coord target_coord;
	t_coord p;
	p.x = game->p_coord.x * 10;
	p.y = game->p_coord.y * 10;
	while (angle < end_angle)
	{
		int wall = '0';
		float raydstx = p.x / 10;
		float raydsty = p.y / 10;
		while (wall == '0' || wall == 'N' || wall == 'S' || wall == 'E' || wall == 'W')
		{
			raydstx += cos(angle);
			raydsty += sin(angle);
			wall = game->map[(int)floorf(raydsty)][(int)floorf(raydstx)];
		}
		target_coord.x = raydstx * 10;
		target_coord.y = raydsty * 10;
		drawline_mini(p, target_coord, game, rgba(251, 124, 114, 1));
		angle += 0.001;
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
			if(game->map[i][j] == '1')
				draw_wall(i * 10, j * 10, game, rgba(255, 255, 255, 1));
			else if (game->map[i][j] == '0' || game->map[i][j] == ' ' || ft_strchr("ESNW", game->map[i][j]))
				draw_wall(i * 10, j * 10, game, rgba(240, 223, 144, 1));
			else if (game->map[i][j] == 'D')
				draw_wall(i * 10, j * 10, game, rgba(107, 68, 0, 1));
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
