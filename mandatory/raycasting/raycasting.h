/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:04:14 by yajallal          #+#    #+#             */
/*   Updated: 2023/07/31 20:10:57 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../parsing/parsing.h"
# include "../structs.h"

void	drawline(t_coord c0, t_coord c1, t_cub *game, int color);

void	key_up(t_cub *game);
void	key_down(t_cub *game);
void	key_right(t_cub *game);
void	key_left(t_cub *game);
void	key_a(t_cub *game);
void	key_d(t_cub *game);
void	hooks(void *ptr);

int		init_game(t_cub *game);
void	find_player(t_cub *game);


void	parse_image(mlx_texture_t *img, int *arr);

void	rays(t_cub *game);
float	normlize_angle(float angle);

double	calc_dis(t_cub *game, t_coord hit, t_coord p);
t_coord	vertical_inter(t_cub *game, t_coord p, t_ray *ray);
t_coord	horizontal_inter(t_cub *game, t_coord p, t_ray *ray);

#endif
