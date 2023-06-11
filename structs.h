/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:38:28 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/11 18:59:02 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#define FOV_ANGLE (60 * (M_PI / 180))
#define WIDTH 640
#define HEIGHT 540
#define ray_inc (FOV_ANGLE / WIDTH)
#define half_fov (FOV_ANGLE / 2)

typedef struct s_map
{
	char *line;
	char cnofig;
	struct s_map *next;

} t_map;

typedef struct s_coord
{
	int x;
	int y;
} t_coord;

typedef struct s_textures
{
	int color_arrayN[(512 * 512)];
	int color_arrayS[(512 * 512)];
	int color_arrayE[(512 * 512)];
	int color_arrayW[(512 * 512)];
} t_textures;


typedef struct s_cub
{
	char **map;
	float player_angle;
	int ciel_color;
	int floor_color;
	t_coord p_coord;
	t_textures *textures;
	mlx_t *mlx;
	mlx_image_t *map_img;
	mlx_image_t *player_img;
	mlx_texture_t *wallN;
	mlx_texture_t *wallS;
	mlx_texture_t *wallW;
	mlx_texture_t *wallE;
} t_cub;

#endif