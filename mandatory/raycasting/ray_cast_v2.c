/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:53:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/06/23 18:28:56 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void drawline_2(int x0, int y0, int x1, int y1, t_cub *game, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	while (x0 != x1 || y0 != y1)
	{
		if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT)
			mlx_put_pixel(game->map_img, x0, y0, color);
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

void ray_cast(t_cub *game)
{
	int count = 0;
	t_coord c0, c1;
	while (count < WIDTH)
	{
		double camx = 2 * count / (double)WIDTH - 1;

		double rayx = game->dda->dirx + game->dda->planex * camx;

		double rayy = game->dda->diry + game->dda->planey * camx;

		// what pos we reached in the map
		int mapx = (int)game->p_coord.x;
		int mapy = (int)game->p_coord.y;
		// length of ray from current pos to next x or y side
		double sidedistx;
		double sidedisty;
		// length of ray from one x or y side to next x or y side
		double deltadistx = (rayx == 0) ? 1e30 : fabs(1 / rayx);
		double deltadisty = (rayy == 0) ? 1e30 : fabs(1 / rayy);
		// wall distance
		double perpwalldist;
		// what direction to step in x or y direction (+1 or -1)
		int stepx;
		int stepy;
		// was there a wall hit?
		int hit = 0;
		// was a NS or a EW wall hit?
		int side;
		// calculate step and initial sideDist
		if (rayx < 0)
		{
			stepx = -1;
			// wall in the north
			sidedistx = (game->p_coord.x - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			// wall in the south
			sidedistx = (mapx + 1.0 - game->p_coord.x) * deltadistx;
		}
		if (rayy < 0)
		{
			stepy = -1;
			// wall in the east
			sidedisty = (game->p_coord.y - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			// wall in the west
			sidedisty = (mapy + 1.0 - game->p_coord.y) * deltadisty;
		}
		// start dda algorithm
		while (hit == 0)
		{
			// moving to next map square in x
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			// moving to next map square in y
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (game->map[mapy][mapx] == '1')
				hit = 1;
		}
		if(side == 0)
			perpwalldist = sidedistx - deltadistx;
		else
			perpwalldist = sidedisty - deltadisty;

		int lineheight = (int)((HEIGHT / 2) / perpwalldist);
		// calc start and point of line to draw
		int drawstart = -lineheight / 2 + HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + HEIGHT / 2;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;

		double wallX;
		if (side == 0)
			wallX = game->p_coord.y + perpwalldist * rayy;
		else
			wallX = game->p_coord.x + perpwalldist * rayx;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)game->wallE->width);
		if (side == 0 && game->dda->dirx > 0)
			texX = game->wallE->width - texX - 1;
		if (side == 1 && game->dda->diry < 0)
			texX = game->wallE->width - texX - 1;

		float yIncr = (float)lineheight * 2 / (float)game->wallE->height;
		t_coord c0, c1;
		float y = (float)(HEIGHT / 2 - lineheight);
		int i = 0;

		while (i < game->wallE->height)
		{
			c0.x = count;
			c0.y = (int)y;
			c1.x = count;
			c1.y = (int)(y + yIncr);
			if (side == 0 && rayx > 0)
				drawline(c0, c1, game, game->textures->color_arrayE[texX + (i * game->wallN->height)]);
			else if (side == 0 && rayx < 0)
				drawline(c0, c1, game, game->textures->color_arrayW[texX + (i * game->wallN->height)]);
			else if (side == 1 && rayy > 0)
				drawline(c0, c1, game, game->textures->color_arrayS[texX + (i * game->wallN->height)]);
			else if (side == 1 && rayy < 0)
				drawline(c0, c1, game, game->textures->color_arrayN[texX + (i * game->wallN->height)]);
			y += yIncr;
			i++;
		}

		c0.x = count,
		c0.y = 0;
		c1.x = count,
		c1.y = drawstart;
		drawline(c0, c1, game, game->ciel_color);
		// c0.x = count,
		// c0.y = drawstart;
		// c1.x = count,
		// c1.y = drawend;
		// drawline(c0, c1, game, rgba(125,15,45,1));
		c0.x = count,
		c0.y = drawend;
		c1.x = count,
		c1.y = HEIGHT;
		drawline(c0, c1, game, game->floor_color);
		count++;
	}
}

// typedef struct s_rays
// {
// 	float rayAngle;
//     float wallHitX;
//     float wallHitY;
//     float distance;
//     int wasHitVertical;
//     int isRayFacingUp;
//     int isRayFacingDown;
//     int isRayFacingLeft;
//     int isRayFacingRight;
//     int wallHitContent;
// } t_rays[WIDTH];

// #define TILE_SIZE 64
// void ray_cast(t_cub *game)
// {
// 	int count = 0;
// 	while (count < WIDTH)
// 	{

// 		float wallStripHeight = (TILE_SIZE)
// 		count++;
// 	}

// }
