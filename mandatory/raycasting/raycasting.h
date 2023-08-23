/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:04:14 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 19:47:19 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../parsing/parsing.h"
# include "../structs.h"

void	error_checker(char **av, t_cub *game, t_map *map);

void	key_up(t_cub *game);
void	key_down(t_cub *game);
void	key_right(t_cub *game);
void	key_left(t_cub *game);

void	pixel_draw(t_coord c0, t_cub *game, int color);
void	drawline(t_coord c0, t_coord c1, t_cub *game, int color);

void	key_left_rotate(t_cub *game);
void	key_right_rotate(t_cub *game);
void	hooks(void *ptr);

void	find_player(t_cub *game);
int		rgba(int r, int g, int b, float t);
void	parse_image(mlx_texture_t *img, int *arr);
int		alloc_textures(t_cub *game);
int		init_game(t_cub *game);

void	intersec_tool(t_cub *game, t_coord *next, t_ray *ray);
t_coord	intersec(t_cub *game, t_ray *ray, char type);
t_coord	horizontal_inter(t_cub *game, t_coord p, t_ray *ray);
t_coord	vertical_inter(t_cub *game, t_coord p, t_ray *ray);

double	calc_dis(t_coord hit, t_coord p);
float	normlize_angle(float angle);

void	raycast(t_cub *game, int rayx, t_ray *ray);
void	rays_drawing(t_cub *game, int i, t_ray *ray, t_coord p);
void	init_sides(t_ray *ray);
void	rays(t_cub *game);

int		*select_texture(t_cub *game, t_ray *ray, float *text_pos_x);
void	draw_texture(t_coord start, t_cub *game, t_ray *ray);

void	free_texturs(t_cub *game);
void	free_colors(t_cub *game);

#endif
