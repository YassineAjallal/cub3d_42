/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:43:26 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/28 19:40:11 by yajallal         ###   ########.fr       */
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
		if (game->map[(int)c0.y / TILE][(int)c0.x / TILE] == '1' || game->map[(int)c0.y / TILE][(int)c0.x / TILE] == 'D')
			break;
        if (c0.x >= 0 && c0.x < 1180 && c0.y >= 0 && c0.y < 560)
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
	// 	if (game->map[(int)c0.y / TILE][(int)c0.x / TILE] == '1' || game->map[(int)c0.y / TILE][(int)c0.x / TILE] == 'D')
	// 		break;
    //     if (c0.x >= 0 && c0.x < 2024 && c0.y >= 0 && c0.y < 2024)
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
// void draw_rays(t_cub *game)
// {
// 	float angle = game->player_angle - FOV_ANGLE / 2;
// 	float end_angle = game->player_angle + FOV_ANGLE / 2;
// 	t_coord target_coord;
// 	t_coord p;
// 	p.x = game->p_coord.x * TILE;
// 	p.y = game->p_coord.y * TILE;
// 	while (angle < end_angle)
// 	{
// 		int wall = '0';
// 		float raydstx = p.x / TILE;
// 		float raydsty = p.y / TILE;
// 		while (wall == '0' || wall == 'N' || wall == 'S' || wall == 'E' || wall == 'W')
// 		{
// 			raydstx += cos(angle);
// 			raydsty += sin(angle);
// 			if (game->map[(int)floorf(raydsty - sin(angle))][(int)floorf(raydstx)] == '1' || game->map[(int)floorf(raydsty)][(int)floorf(raydstx - cos(angle))] == '1')
// 			{
// 				break;
// 			}
// 			wall = game->map[(int)floorf(raydsty)][(int)floorf(raydstx)];
// 		}
// 		target_coord.x = raydstx * TILE;
// 		target_coord.y = raydsty * TILE;
// 		drawline_mini(p, target_coord, game, rgba(251, 124, 114, 1));
// 		angle += ray_inc;
// 	}
// }

// void draw_ray(t_cub *game, float angle, int step, int color)
// {
// 	t_coord t;
// 	t_coord t0;
// 	t0.x = game->p_coord.x * TILE;
// 	t0.y = game->p_coord.y * TILE;
// 	t.x = ((game->p_coord.x * TILE) + (cos(angle) * step));
// 	t.y = ((game->p_coord.y * TILE) + (sin(angle) * step));
// 	drawline_mini(t, t0, game, color);
// }

// t_coord vertical_inter(t_cub *game, float angle)
// {
// 	t_coord result;
// 	angle = normlize_angle(angle);
// 	float xstep, ystep;
// 	float xintercept, yintercept;
// 	bool up = 0, down = 0, left = 0, right = 0;


// 	if (angle > 0 && angle < M_PI)
// 		down = 1;
// 	else
// 		up = !down;

// 	if (angle < M_PI / 2 || angle > (3 * M_PI) / 2)
// 		left = 1;
// 	else
// 		right = !left;
// 	xintercept = floorf(((game->p_coord.x * TILE) / TILE) * TILE);
// 	xintercept += right ? TILE : 0;

// 	yintercept = (game->p_coord.y * TILE) + ((xintercept - (game->p_coord.x * TILE)) / tan(angle));

// 	xstep = TILE;
// 	xstep *= left ? -1 : 1;

// 	ystep = TILE * tan(angle);
// 	ystep *= (up && ystep > 0) ? -1 : 1;
// 	ystep *= (down && ystep < 0) ? -1 : 1;

// 	float next_V_x = xintercept;
// 	float next_V_y = yintercept;
	
// 	if (left)
// 		next_V_x--;
// 	while(next_V_x > 0 && next_V_y > 0 && next_V_x < 1180 && next_V_y < HEIGHT)
// 	{
// 		if ((int)floorf(next_V_y / TILE) > 13)
// 			break;
// 		if ((int)floorf(next_V_x / TILE) > ft_strlen(game->map[(int)floorf(next_V_y / TILE)]) - 1)
// 			break;
// 		if (game->map[(int)floorf(next_V_y / TILE)][(int)floorf(next_V_x / TILE)] == '1')
// 		{
// 			result.x = next_V_x;
// 			result.y = next_V_y;
// 			break;
// 		}
// 		next_V_x += xstep;
// 		next_V_y += ystep;
// 	}
// 	return (result);
// }

float calc_dis(t_cub *game, t_coord hit, t_coord p)
{
	float dis;
	dis = sqrt(pow(p.x - hit.x, 2) + pow(p.y - hit.y, 2));
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
			mlx_put_pixel(game->minimap_img, i, j, color);
			j++;
		}
		i++;
	}

}

void draw_player(int h, int w, t_cub *game, int color)
{
	int i =  h + 10;
	while (i <= h + 20)
	{
		int j = w + 10;
		while (j <= w + 20)
		{
			mlx_put_pixel(game->minimap_img, i, j, color);
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
			else if (game->map[i][j] == '0' || game->map[i][j] == ' ' || ft_strchr("ESNW", game->map[i][j]))
				draw_wall(j * TILE, i * TILE, game, rgba(0, 0, 0, 1));
			j++;
		}
		i++;
	}
	// draw_player((int)game->p_coord.x * TILE, (int)game->p_coord.y * TILE, game, rgba(200, 200, 200, 1));
}

void put_minimap(t_cub *game)
{
	draw_maps(game);
	// draw_ray(game, game->player_angle, 50, rgba(100, 155, 10, 1));
	rays(game);
	mlx_image_to_window(game->mlx, game->minimap_img, 50, 0);
}
