/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/07/30 15:34:08 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"


void draw_Texture(int x, int wall_height, int textPosX, t_cub *game, int *arr, mlx_texture_t *img)
{
	float yIncr = (float)wall_height * 2 / (float)img->height;
	t_coord c0, c1;
	float y = (float)(HEIGHT / 2 - wall_height);
	int i = 0;

	while (i < img->height)
	{
		c0.x = x;
		c0.y = (int)y;
		c1.x = x;
		c1.y = (int)(y + yIncr);
		drawline(c0, c1, game, arr[textPosX + (i * img->height)]);
		y += yIncr;
		i++;
	}
}

void setup_textures(t_cub *game, float ray_x, float ray_y, float raycos, float raysin, int count, float wall_height)
{
	float prev_x = ray_x - raycos;
	float prev_y = ray_y - raysin;
	float delta_x = fabs(ray_x - floor(ray_x + 0.5));
	float delta_y = fabs(ray_y - floor(ray_y + 0.5));
	float ray_angle = game->player_angle - half_fov;
	float wallWidth = game->wallN->width;
	float posXFloat = wallWidth * (prev_x + prev_y);
	char direction;

	int textposX = (int)posXFloat % game->wallN->width;
	if (delta_x < delta_y)
	{
    	if (raycos > 0)
        	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayE, game->wallE);
    	else
        	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayW, game->wallW);
	}
	else
	{
    	if (raysin > 0)
        	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayS, game->wallS);
    	else
        	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayN, game->wallN);
	}
}

void raycast(t_cub *game, float distance, int ray, double angle)
{
	t_coord start, end;
	int proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	distance = distance * cos(angle - game->player_angle);
	int wallStripHeight = (TILE / distance) * proj_plane;
	start.x = ray;
	end.x = ray;
	start.y = (HEIGHT / 2) - (wallStripHeight / 2);
	end.y = (HEIGHT / 2) + (wallStripHeight / 2);
	drawline(start, end, game, rgba(25,25,25,1));
}

void rays(t_cub *game)
{
	double angle = game->player_angle - (FOV_ANGLE / 2);
	t_coord hor, ver;
	double horDis, verDis;
	t_coord p;

	int i = 0;
	p.x = game->p_coord.x * TILE;
	p.y = game->p_coord.y * TILE;
	while (i < WIDTH)
	{
		int j = -1;
		while (++j < HEIGHT)
		{
			if (j <= (HEIGHT / 2))
				mlx_put_pixel(game->map_img, i, j, rgba(0,0,255,1));
			else
				mlx_put_pixel(game->map_img, i, j, rgba(0,255,0,1));	
		}
		ver = vertical_inter(game, angle, p);
		hor = horizontal_inter(game, angle, p);
		verDis = calc_dis(game, ver, p);
		horDis = calc_dis(game, hor, p);
		if (horDis > verDis)
			raycast(game, verDis, i, angle);
		else
			raycast(game, horDis, i, angle);
		angle += ray_inc;
		i++;
	}
	put_minimap(game);
	mlx_image_to_window(game->mlx, game->map_img, 0, 0);
}

