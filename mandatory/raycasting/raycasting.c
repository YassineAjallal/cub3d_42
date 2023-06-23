/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/06/22 15:59:58 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void draw_Texture(int x, int wall_height, int textPosX, t_cub *game, int *arr)
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

void setup_textures(t_cub *game, float ray_x, float ray_y, float raycos, float raysin, int count, float wall_height)
{
	float prev_x = ray_x - raycos;
	float prev_y = ray_y - raysin;
	float posXFloat;
	int textposX;
	float delta_x = fabs(ray_x - floor(ray_x + 0.5));
	float delta_y = fabs(ray_y - floor(ray_y + 0.5));
	if (delta_x <= delta_y)
	{
    	if (raycos > 0)
		{
			posXFloat = game->wallE->width * (ray_x + ray_y);
			textposX = (int)posXFloat % game->wallE->width;
        	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayE);
		}
    	else
		{
			posXFloat = game->wallW->width * (ray_x + ray_y);
			textposX = (int)posXFloat % game->wallW->width;
        	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayW);
		}
	}
	else
	{
    	if (raysin > 0)
		{
			posXFloat = game->wallS->width * (ray_x + ray_y);
			textposX = (int)posXFloat % game->wallS->width;
        	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayS);
		}
    	else
		{
			posXFloat = game->wallN->width * (ray_x + ray_y);
			textposX = (int)posXFloat % game->wallN->width;
        	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayN);
		}
	}
}

// void ray_cast(t_cub *game)
// {
// 	float ray_angle;
// 	float count;
// 	float ray_x;
// 	float ray_y;
// 	float raycos;
// 	float raysin;
// 	char wall;
// 	t_coord c0, c1;

// 	ray_angle = game->player_angle - HALF_FOV;
// 	count = 0;
// 	while (count < WIDTH)
// 	{
// 		ray_x = (float)game->p_coord.x;
// 		ray_y = (float)game->p_coord.y;
// 		raycos = cos(ray_angle) / 512;
// 		raysin = sin(ray_angle) / 512;
// 		wall = '0';

// 		while (wall == '0'  || wall == 'N' || wall == 'S' || wall == 'E' || wall == 'W')
// 		{
// 			ray_x += raycos;
// 			ray_y += raysin;
// 			wall = game->map[(int)floorf(ray_y)][(int)floorf(ray_x)];
// 		}
// 		float distance = sqrtf((ray_x - game->p_coord.x) * (ray_x - game->p_coord.x) + (ray_y - game->p_coord.y) * (ray_y - game->p_coord.y));
// 		distance = distance * cos(ray_angle - game->player_angle);
// 		int wall_height = (int)floorf(((HEIGHT / 2)/  distance));
// 		c0.x = count,
// 		c0.y = 0;
// 		c1.x = count,
// 		c1.y = (HEIGHT / 2) - wall_height;
// 		drawline(c0, c1, game, game->ciel_color);
// 		setup_textures(game, ray_x, ray_y, raycos, raysin, count, wall_height);
// 		c0.x = count,
// 		c0.y = (HEIGHT / 2) + wall_height;
// 		c1.x = count,
// 		c1.y = HEIGHT;
// 		drawline(c0, c1, game, game->floor_color);
// 		ray_angle += RAY_INC;
// 		count++;
// 	}
// }
