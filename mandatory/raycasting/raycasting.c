/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/07/31 14:29:58 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"


// void draw_Texture(int x, int wall_height, int textPosX, t_cub *game, int *arr, mlx_texture_t *img)
// {
// 	float yIncr = (float)wall_height * 2 / (float)img->height;
// 	t_coord c0, c1;
// 	float y = (float)(HEIGHT / 2 - wall_height);
// 	int i = 0;

// 	while (i < img->height)
// 	{
// 		c0.x = x;
// 		c0.y = (int)y;
// 		c1.x = x;
// 		c1.y = (int)(y + yIncr);
// 		drawline(c0, c1, game, arr[textPosX + (i * img->height)]);
// 		y += yIncr;
// 		i++;
// 	}
// }

// void setup_textures(t_cub *game, float ray_x, float ray_y, float raycos, float raysin, int count, float wall_height)
// {
// 	float prev_x = ray_x - raycos;
// 	float prev_y = ray_y - raysin;
// 	float delta_x = fabs(ray_x - floor(ray_x + 0.5));
// 	float delta_y = fabs(ray_y - floor(ray_y + 0.5));
// 	float ray_angle = game->player_angle - HALF_FOV;
// 	float wallWidth = game->wallN->width;
// 	float posXFloat = wallWidth * (prev_x + prev_y);
// 	char direction;

// 	int textposX = (int)posXFloat % game->wallN->width;
// 	if (delta_x < delta_y)
// 	{
//     	if (raycos > 0)
//         	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayE, game->wallE);
//     	else
//         	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayW, game->wallW);
// 	}
// 	else
// 	{
//     	if (raysin > 0)
//         	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayS, game->wallS);
//     	else
//         	draw_Texture(count, wall_height, textposX, game, game->textures->color_arrayN, game->wallN);
// 	}
// }
void draw_texture(t_coord start, t_coord end, t_cub *game, int wall_height, t_ray *ray, t_coord verHor, char type)
{
	float yIncr = (float)wall_height / (float)game->wallN->height;
	t_coord c0, c1;
	int *color;
	float y = start.y;
	float textPosX;
	int i = 0;
	if (type == 'v')
	{
		int ray_direction = (int)(ray->angle * 180 / M_PI);
		int fixed = verHor.y - (verHor.y / TILE) * TILE;
		textPosX = (verHor.y - fixed) * game->wallS->width / TILE;
		if (ray_direction > 90 && ray_direction < 270)
			color = game->textures->color_arrayS;
		else
			color = game->textures->color_arrayE;
	}
	else
	{
		int ray_direction = (int)(ray->angle * 180 / M_PI);
		int fixed = verHor.x - (verHor.x / TILE) * TILE;
		textPosX = (verHor.x - fixed) * game->wallS->width / TILE;
		if (ray_direction > 0 && ray_direction < 180)
			color = game->textures->color_arrayN;
		else
			color = game->textures->color_arrayW;
	}
	int posx = (int)textPosX;
	while (i < game->wallN->height)
	{
		c0.x = start.x;
		c0.y = (int)y;
		c1.x = start.x;
		c1.y = (int)(y + yIncr);
		// drawline(c0, c1, game, color[ posx + (i * game->wallN->width)]);
		// printf("%d\n", );
		y += yIncr;
		i++;
	}
}

void raycast(t_cub *game, int rayx, t_ray *ray, double distance, t_coord verHor, char type)
{
	t_coord start;
	t_coord end;
	int proj_plane;
	int wallStripHeight;

	proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	distance = distance * cos(ray->angle - game->player_angle);
	wallStripHeight = (TILE / distance) * proj_plane;
	start.x = rayx;
	end.x = rayx;
	start.y = (HEIGHT / 2) - (wallStripHeight / 2);
	end.y = (HEIGHT / 2) + (wallStripHeight / 2);
	// drawline(start, end, game, rgba(25,25,25,1));
	draw_texture(start, end, game, wallStripHeight, ray, verHor, type);
}

void rays(t_cub *game)
{
	t_coord hor;
	t_coord ver;
	t_ray ray;
	double horDis;
	double verDis;
	t_coord p;
	int j;

	int i = 0;
	p.x = game->p_coord.x * TILE;
	p.y = game->p_coord.y * TILE;
	ray.angle = game->player_angle - (FOV_ANGLE / 2);
	while (i < WIDTH)
	{
		ray.angle = normlize_angle(ray.angle);
		ray.down = ray.angle > 0 && ray.angle < M_PI;
		ray.up = !ray.down;
		ray.right = (ray.angle < (0.5 * M_PI)) || (ray.angle > (1.5 * M_PI));
		ray.left = !ray.right;
		j = -1;
		while (++j < HEIGHT)
		{
			if (j <= (HEIGHT / 2))
				mlx_put_pixel(game->map_img, i, j, game->ciel_color);
			else
				mlx_put_pixel(game->map_img, i, j, game->floor_color);	
		}
		ver = vertical_inter(game, p, &ray);
		hor = horizontal_inter(game, p, &ray);
		verDis = calc_dis(game, ver, p);
		horDis = calc_dis(game, hor, p);
		if (horDis > verDis)
			raycast(game,i, &ray, verDis, ver, 'v');
		else
			raycast(game, i, &ray, horDis, hor, 'h');
		ray.angle += RAY_INC;
		i++;
	}
}

