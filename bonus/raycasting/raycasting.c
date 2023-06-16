/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/06/16 12:09:15 by yajallal         ###   ########.fr       */
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

void ray_cast(t_cub *game)
{
	float ray_angle;
	float count;
	float ray_x;
	float ray_y;
	float raycos;
	float raysin;
	char wall;
	t_coord c0, c1;

	ray_angle = game->player_angle - half_fov;
	count = 0;
	while (count < WIDTH)
	{
		if(game->index > 2)
			game->index = 0;
		ray_x = (float)game->p_coord.x;
		ray_y = (float)game->p_coord.y;
		raycos = cos(ray_angle) / 512;
		raysin = sin(ray_angle) / 512;
		wall = '0';

		while (wall == '0'  || wall == 'N' || wall == 'S' || wall == 'E' || wall == 'W')
		{
			ray_x += raycos;
			ray_y += raysin;
			wall = game->map[(int)floorf(ray_y)][(int)floorf(ray_x)];
		}
		float distance = sqrtf((ray_x - game->p_coord.x) * (ray_x - game->p_coord.x) + (ray_y - game->p_coord.y) * (ray_y - game->p_coord.y));
		distance = distance * cos(ray_angle - game->player_angle);
		int wall_height = (int)floorf(((HEIGHT / 2) / distance));

		c0.x = count,
		c0.y = 0;
		c1.x = count,
		c1.y = (HEIGHT / 2) - wall_height;
		drawline(c0, c1, game, game->ciel_color);
		if(wall == '1')
			setup_textures(game, ray_x, ray_y, raycos, raysin, count, wall_height);
		else if(wall == 'D')
		{
			float prev_x = ray_x - raycos;
			float prev_y = ray_y - raysin;
			float wallWidth = game->dooR->width;
			float posXFloat = wallWidth * (prev_x + prev_y);
			char direction;

			int textposX = (int)posXFloat % game->dooR->width;
			draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayD, game->dooR);
		}
		c0.x = count,
		c0.y = (HEIGHT / 2) + wall_height;
		c1.x = count,
		c1.y = HEIGHT;
		drawline(c0, c1, game, game->floor_color);
		ray_angle += ray_inc;
		count++;
	}
	game->index++;
}
