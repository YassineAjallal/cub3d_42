/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:45:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 18:36:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// float normlize_angle(float angle)
// {
// 	angle = remainder(angle, 2 * M_PI);
// 	if (angle < 0)
//         angle += 2 * M_PI;
// 	return (angle);
// }

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

// t_coord horizontal_inter(t_cub *game, double angle, t_coord p)
// {
// 	t_coord intercept;
// 	t_coord step;
// 	angle = normlize_angle(angle);

// 	bool down = angle > 0 && angle < M_PI;
// 	bool up = !down;
// 	bool right = (angle < (0.5 * M_PI)) || (angle > (1.5 * M_PI));
// 	bool left = !right ;

// 	intercept.y = (((int)p.y / TILE) * TILE);
// 	intercept.y += down ? TILE : 0;
// 	intercept.x = p.x + ((intercept.y - p.y) / tan(angle));

// 	step.y = TILE;
// 	step.y *= up ? -1 : 1;
// 	step.x = TILE / tan(angle);
// 	step.x *= (left && step.x > 0) ? -1 : 1;
// 	step.x *= (right && step.x < 0) ? -1 : 1;

// 	t_coord next;

// 	next.x = intercept.x;
// 	next.y = intercept.y;
// 	if (up)
// 		next.y--;
// 	t_coord result;
// 	while(next.x >= 0 && next.y >= 0 && next.x <= game->large_length * TILE && next.y <= game->map_len * TILE)
// 	{
// 		if ((int)floorf(next.y / TILE) >= ft_strlen2d(game->map))
// 			break;
// 		if ((int)floorf(next.x / TILE) >= ft_strlen(game->map[(int)floorf(next.y / TILE)]))
// 			break;
// 		if (game->map[(int)floorf(next.y / TILE)][(int)floorf(next.x / TILE)] == '1')
// 			break;
// 		else
// 		{
// 			next.x += step.x;
// 			next.y += step.y;
// 		}
// 	}
// 	if (up)
// 		next.y++;
// 	result.x = next.x;
// 	result.y = next.y;
// 	return (result);
// }

// t_coord vertical_inter(t_cub *game, double angle, t_coord p)
// {
// 	t_coord intercept;
// 	t_coord step;
// 	angle = normlize_angle(angle);

// 	bool down = angle > 0 && angle < M_PI;
// 	bool up = !down;
// 	bool right = (angle < (0.5 * M_PI)) || (angle > (1.5 * M_PI));
// 	bool left = !right ;

// 	intercept.x = (((int)p.x / TILE) * TILE);
// 	intercept.x += right ? TILE : 0;
// 	intercept.y = p.y + ((intercept.x - p.x) * tan(angle));

// 	step.x = TILE;
// 	step.x *= left ? -1 : 1;

// 	step.y = TILE * tan(angle);
// 	step.y *= (up && step.y > 0) ? -1 : 1;
// 	step.y *= (down && step.y < 0) ? -1 : 1;
// 	t_coord next;

// 	next.x = intercept.x;
// 	next.y = intercept.y;
// 	if (left)
// 		next.x--;
// 	t_coord result;
// 	while(next.x >= 0 && next.y >= 0 && game->large_length * TILE && next.y <= game->map_len * TILE)
// 	{
// 		if ((int)floorf(next.y / TILE) >= ft_strlen2d(game->map))
// 			break;
// 		if ((int)floorf(next.x / TILE) >= ft_strlen(game->map[(int)floorf(next.y / TILE)]))
// 			break;
// 		if (game->map[(int)floorf(next.y / TILE)][(int)floorf(next.x / TILE)] == '1')
// 			break;
// 		else
// 		{
// 			next.x += step.x;
// 			next.y += step.y;
// 		}
// 	}
// 	if (left)
// 		next.x++;
// 	result.x = next.x;
// 	result.y = next.y;
// 	return (result);
// }

void rays_minimap(t_cub *game)
{
	t_coord	hor;
	t_coord	ver;
	t_ray	ray;
	double	horDis;
	double	verDis;
	t_coord	p;
	int		j;
	int		i;

	i = 0;
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
		ver = vertical_inter(game, p, &ray);
		hor = horizontal_inter(game, p, &ray);
		verDis = calc_dis(game, ver, p);
		horDis = calc_dis(game, hor, p);
		if (horDis > verDis)
			drawline_mini(p, ver, game, rgba(255,0,0,1));
		else
			drawline_mini(p, hor, game, rgba(255,0,0,1));
		ray.angle += RAY_INC;
		i++;
	}
}