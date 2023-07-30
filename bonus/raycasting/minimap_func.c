/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:45:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/30 12:08:22 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

float normlize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
        angle += 2 * M_PI;
	return (angle);
}

// t_coord intersec(t_cub *game, t_coord intercept, t_coord step)
// {
// 	t_coord result;
// 	t_coord next;

// 	next.x = intercept.x;
// 	next.y = intercept.y;
// 	while(next.x > 0 && next.y > 0 && next.x < 1180 && next.y < HEIGHT)
// 	{
// 		if ((int)floorf(next.y / TILE) >= ft_strlen2d(game->map))
// 			break;
// 		if ((int)floorf(next.x / TILE) >= ft_strlen(game->map[(int)floorf(next.y / TILE)]))
// 			break;
// 		if (game->map[(int)floorf(next.y / TILE)][(int)floorf(next.x / TILE)] == '1')
// 			break;
// 		next.x += step.x;
// 		next.y += step.y;
// 	}
// 	result.x = next.x;
// 	result.y = next.y;
// 	return (result);
// }

t_coord horizontal_inter(t_cub *game, double angle, t_coord p)
{
	t_coord intercept;
	t_coord step;
	angle = normlize_angle(angle);

	bool down = angle > 0 && angle < M_PI;
	bool up = !down;
	bool right = (angle < (0.5 * M_PI)) || (angle > (1.5 * M_PI));
	bool left = !right ;

	intercept.y = (((int)p.y / TILE) * TILE);
	intercept.y += down ? TILE : 0;
	intercept.x = p.x + ((intercept.y - p.y) / tan(angle));

	step.y = TILE;
	step.y *= up ? -1 : 1;
	step.x = TILE / tan(angle);
	step.x *= (left && step.x > 0) ? -1 : 1;
	step.x *= (right && step.x < 0) ? -1 : 1;

	t_coord next;

	next.x = intercept.x;
	next.y = intercept.y;
	if (up)
		next.y--;
	t_coord result;
	while(next.x >= 0 && next.y >= 0 && next.x <= 1180 && next.y <= HEIGHT)
	{
		if ((int)floorf(next.y / TILE) >= ft_strlen2d(game->map))
			break;
		if ((int)floorf(next.x / TILE) >= ft_strlen(game->map[(int)floorf(next.y / TILE)]))
			break;
		if (game->map[(int)floorf(next.y / TILE)][(int)floorf(next.x / TILE)] == '1')
			break;
		else
		{
			next.x += step.x;
			next.y += step.y;
		}
	}
	if (up)
		next.y++;
	result.x = next.x;
	result.y = next.y;
	return (result);
}

t_coord correct(t_coord c0, t_coord c1, t_cub *game)
{
    // int dx = abs((int)c1.x - (int)c0.x);
    // int dy = abs((int)c1.y - (int)c0.y);
    // int sx = (int)c0.x < (int)c1.x ? 1 : -1;
    // int sy = (int)c0.y < (int)c1.y ? 1 : -1;
	t_coord result;
    // int err = dx - dy;

    // while ((int)c0.x != (int)c1.x || (int)c0.y != (int)c1.y)
    // {
	// 	if (game->map[(int)c0.y / TILE][(int)c0.x / TILE] == '1' || game->map[(int)c0.y / TILE][(int)c0.x / TILE] == 'D')
	// 		break;
    //     // if (c0.x >= 0 && c0.x < 1180 && c0.y >= 0 && c0.y < 560)
    //     // 	mlx_put_pixel(game->minimap_img, c0.x, c0.y, color);
    //     int err2 = 2 * err;
    //     if (err2 > -dy)
    //     {
    //         err -= dy;
    //         c0.x += sx;
    //     }
    //     if (err2 < dx)
    //     {
    //         err += dx;
    //         c0.y += sy;
    //     }
    // }
	int dx = (int)c1.x - (int)c0.x;
    int dy = (int)c1.y - (int)c0.y;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;

    float x = (int)c0.x;
    float y = (int)c0.y;

    for (int i = 0; i <= steps; i++) {

        x += xIncrement;
        y += yIncrement;
    }
	result.x = c0.x;
	result.y = c0.y;
	return (result);
}

t_coord vertical_inter(t_cub *game, double angle, t_coord p)
{
	t_coord intercept;
	t_coord step;
	angle = normlize_angle(angle);

	bool down = angle > 0 && angle < M_PI;
	bool up = !down;
	bool right = (angle < (0.5 * M_PI)) || (angle > (1.5 * M_PI));
	bool left = !right ;

	intercept.x = (((int)p.x / TILE) * TILE);
	intercept.x += right ? TILE : 0;
	intercept.y = p.y + ((intercept.x - p.x) * tan(angle));

	step.x = TILE;
	step.x *= left ? -1 : 1;

	step.y = TILE * tan(angle);
	step.y *= (up && step.y > 0) ? -1 : 1;
	step.y *= (down && step.y < 0) ? -1 : 1;
	t_coord next;

	next.x = intercept.x;
	next.y = intercept.y;
	if (left)
		next.x--;
	t_coord result;
	while(next.x >= 0 && next.y >= 0 && next.x <= 1180 && next.y <= HEIGHT)
	{
		if ((int)floorf(next.y / TILE) >= ft_strlen2d(game->map))
			break;
		if ((int)floorf(next.x / TILE) >= ft_strlen(game->map[(int)floorf(next.y / TILE)]))
			break;
		if (game->map[(int)floorf(next.y / TILE)][(int)floorf(next.x / TILE)] == '1')
			break;
		else
		{
			next.x += step.x;
			next.y += step.y;
		}
	}
	if (left)
		next.x++;
	result.x = next.x;
	result.y = next.y;
	return (result);
}
void raycast(t_cub *game, float distance, int ray)
{
	t_coord ciel, wall;
	int proj_plane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	int wallStripHeight = (TILE / distance) * proj_plane;
	ciel.x = ray;
	ciel.y = 0;
	wall.x = ray;
	wall.y = (HEIGHT / 2) - (wallStripHeight / 2);
	drawline(ciel, wall, game, rgba(0,0,255,1));
	ciel.y = (HEIGHT / 2) - (wallStripHeight / 2);
	wall.y = (HEIGHT / 2) + wallStripHeight;
	drawline_mini(ciel, wall, game, rgba(48,18,64,1));
	ciel.y = (HEIGHT / 2) + wallStripHeight;
	wall.y = HEIGHT;
	drawline(ciel, wall, game, rgba(0,255,0,1));
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
		ver = vertical_inter(game, angle, p);
		hor = horizontal_inter(game, angle, p);
		// ver = correct(p, ver, game);
		verDis = calc_dis(game, ver, p);
		horDis = calc_dis(game, hor, p);
		if (horDis > verDis)
		{
			// drawline(p, ver, game, rgba(255, 25,255,1));
			raycast(game, verDis, i);
		}
		else
		{
			// drawline(p, hor, game, rgba(25, 225,255,1));
			raycast(game, horDis, i);
		}
		angle += ray_inc;
		i++;
	}
}
