/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/06/11 19:37:53 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void draw_Texture(int x, int wall_height, int textPosX, t_cub *game, int arr[512 * 512])
{
	float yIncr = (float)wall_height * 2 / (float)game->wallN->height;
	t_coord c0, c1;
	float y = (float)(HEIGHT / 2 - wall_height);
	int i = 0;

	while (i < game->wallN->height)
	{
		c0.x = x;
		c0.y = (int)y;
		c1.x = x;
		c1.y = (int)(y + yIncr);
		drawline(c0, c1, game, arr[textPosX + (i * game->wallN->height)]);
		y += yIncr;
		i++;
	}
}

void setup_textures(t_cub *game, float ray_x, float ray_y, float raycos, float raysin, int count)
{
	float prev_x = ray_x - raycos;
	float prev_y = ray_y - raysin;
	float delta_x = ray_x - prev_x;
	float delta_y = ray_y - prev_y;
	float 	ray_angle = game->player_angle - half_fov;
	float distance = sqrtf((ray_x - game->p_coord.x) * (ray_x - game->p_coord.x) + (ray_y - game->p_coord.y) * (ray_y - game->p_coord.y));
	distance = distance * cos(ray_angle - game->player_angle);
	int wall_height = (int)floorf(((HEIGHT / 2) / distance));
	float wallWidth = game->wallN->width;
	float posXFloat = wallWidth * (ray_x + ray_y);

	int textposX = (int)posXFloat % game->wallN->width;
		// if((int)floorf(ray_y) == 0)
		// 	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayN);
		// else if ((int)floorf(ray_y) == 19)
		// 	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayS);
		// else if((int)floorf(ray_x) == 0)
		// 	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayE);
		// else if((int)floorf(ray_x) == 9)
		// 	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayW);
		// else
			draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayE);
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
		float distance = sqrtf((ray_x - game->p_coord.x) * (ray_x - game->p_coord.x) + (ray_y - game->p_coord.y) * (ray_y - game->p_coord.y));
		ray_x = (float)game->p_coord.x;
		ray_y = (float)game->p_coord.y;
		raycos = cos(ray_angle) / 64;
		raysin = sin(ray_angle) / 64;
		wall = '0';

		while (wall == '0'  || wall == 'N' || wall == 'S' || wall == 'E' || wall == 'W')
		{
			ray_x += raycos;
			ray_y += raysin;
			wall = game->map[(int)floorf(ray_y)][(int)floorf(ray_x)];
		}
		distance = distance * cos(ray_angle - game->player_angle);
		int wall_height = (int)floorf(((HEIGHT / 2) / distance));

		c0.x = count,
		c0.y = 0;
		c1.x = count,
		c1.y = (HEIGHT / 2) - wall_height;
		drawline(c0, c1, game, rgba(80, 130, 200, 1));
		setup_textures(game, ray_x, ray_y, raycos, raysin, count);
		c0.x = count,
		c0.y = (HEIGHT / 2) + wall_height;
		c1.x = count,
		c1.y = HEIGHT;
		drawline(c0, c1, game, rgba(98, 105, 109, 1));
		ray_angle += ray_inc;
		count++;
	}
}
