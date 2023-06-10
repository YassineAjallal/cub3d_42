/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/06/10 19:28:05 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TILE_SIZE 32
#define PI M_PI
#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS 40 * 10
#define height 40 * 20
#define ray_inc (FOV_ANGLE / NUM_RAYS)
#define half_fov (FOV_ANGLE / 2)
#define scale 1


float player_angel = (PI/2);
float p_x;
float p_y;


char r_map[20][10] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '1', '0', '1'},
	{'1', '0', 'E', '0', '1', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

typedef struct t_cub
{
	mlx_t *mlx;
	mlx_image_t *map;
	mlx_image_t *player;
	mlx_texture_t *wallN;
	mlx_texture_t *wallS;
	mlx_texture_t *wallW;
	mlx_texture_t *wallE;
	xpm_t *xpm_w;
} s_cub;

s_cub cub;

int ft_s(int s0, int s1)
{
	if (s0 < s1)
		return (1);
	return (-1);
}

void drawline(int x0, int y0, int x1, int y1, unsigned int colore)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (x0 != x1 || y0 != y1)
    {
		if (r_map[y0 / 40][x0 / 40] == '1')
			break;
        mlx_put_pixel(cub.map, x0, y0, colore);
        int err2 = 2 * err;
        if (err2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
void angle_to_unit_vector(float angle, float *x, float *y)
{
    float radians = angle * PI / 180.0;
    *x = cos(radians);
    *y = sin(radians);
}

void draw_rays()
{
	float angle = player_angel - FOV_ANGLE / 2;
    float end_angle = player_angel + FOV_ANGLE / 2;
	float target_x;
	float target_y;


	while (angle < end_angle)
	{
		target_x = p_x + cos(angle) * 500;
		target_y = p_y + sin(angle) * 500;
		drawline(p_x, p_y, target_x, target_y, 0xFF0000FF);
		angle += 0.001;
	}
}

void find_player()
{
	int i = 0;
	int j;

	while (i < 20)
	{
		j = 0;
		while (j < 10)
		{
			if (r_map[i][j] == 'N' || r_map[i][j] == 'S' || r_map[i][j] == 'E' || r_map[i][j] == 'W')
			{
				p_x = j * 40;
				p_y = i * 40;
				if(r_map[i][j] == 'N')
					player_angel = 3 * PI / 2;
				if(r_map[i][j] == 'S')
					player_angel = PI / 2;
				if(r_map[i][j] == 'E')
					player_angel = 0;
				if(r_map[i][j] == 'W')
					player_angel = PI;
				return;
			}
			j++;
		}
		i++;
	}
}
void	drw_wall(int h, int w, int color)
{
	int i = h;
	while (i < h + 40)
	{
		int j = w;
		while (j < w + 40)
		{
			if (i == h + 39 || i == h || j == w + 39 || j == w)
				mlx_put_pixel(cub.map, j, i, 0x00000000);
			else
				mlx_put_pixel(cub.map, j, i, color);
			j++;
		}
		
		i++;
	}
	
}
void	draw_maps()
{
	int i = 0;
	while (i < 20)
	{
		int j = 0;
		while (j < 10)
		{
			if(r_map[i][j] == '1')
				drw_wall(i * 40, j * 40, 0xFFFFFFAA);
			else
				drw_wall(i * 40, j * 40,0x00000000);
			j++;
		}
		
		i++;
	}
}
void drw_pixels()
{
	draw_maps();
	draw_rays();
}

void hooks()
{
	if (mlx_is_key_down(cub.mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(cub.mlx, MLX_KEY_UP))
	{
		float playercos = cos(player_angel);
		float playersin = sin(player_angel);
		float tmpx = p_x + playercos;
		float tmpy = p_y + playersin;
		if (r_map[(int)floorf(tmpy) / 40][(int)floorf(tmpx) / 40] != '1')
		{
			p_y = tmpy;
			p_x = tmpx;

		}
	}
	if (mlx_is_key_down(cub.mlx, MLX_KEY_DOWN))
	{
		float playercos = cos(player_angel);
		float playersin = sin(player_angel);
		float tmpx = p_x - playercos;
		float tmpy = p_y - playersin;
		if (r_map[(int)floorf(tmpy) / 40][(int)floorf(tmpx) /40] != '1')
		{
			p_y = tmpy;
			p_x = tmpx;
		}
	}
	if (mlx_is_key_down(cub.mlx, MLX_KEY_A))
	{
		player_angel -= 0.05;
		if (player_angel < 0)
			player_angel += 2 * M_PI;
		else if (player_angel > 2 * M_PI)
			player_angel -= 2 * M_PI;
	}
	if (mlx_is_key_down(cub.mlx, MLX_KEY_D))
	{
		player_angel += 0.05;
		if (player_angel < 0)
			player_angel += 2 * M_PI;
		else if (player_angel > 2 * M_PI)
			player_angel -= 2 * M_PI;
	}
	drw_pixels();
}

int main()
{
	cub.mlx = mlx_init(NUM_RAYS, height, "CUB3D", 0);

	cub.map = mlx_new_image(cub.mlx, NUM_RAYS, height);
	mlx_image_to_window(cub.mlx, cub.map, 0, 0);
	draw_maps();
	find_player();

	mlx_loop_hook(cub.mlx, hooks,NULL);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (0);
}

