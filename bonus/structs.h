/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:38:28 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 20:05:28 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42
# define SCALE_MINIMAP 0.1
# define TILE 64
# define WIDTH 720
# define HEIGHT 720

typedef enum e_side
{
	NO,
	SO,
	WE,
	EA
}	t_side;

typedef struct s_coord
{
	float			x;
	float			y;
}					t_coord;

typedef struct s_ray
{
	bool			down;
	bool			up;
	bool			right;
	bool			left;
	double			angle;
	double			distance;
	t_coord			wall_coord;
	char			dir;
	int				wall_height;
	t_coord			intercept;
	t_coord			step;
}					t_ray;
typedef struct s_map
{
	char			*line;
	char			cnofig;
	struct s_map	*next;

}					t_map;

typedef struct s_textures
{
	int				*color_arrayn;
	int				*color_arrays;
	int				*color_arraye;
	int				*color_arrayw;
}					t_textures;

typedef struct s_cub
{
	char			**map;
	int				map_len;
	int				large_length;
	float			player_angle;
	int				ciel_color;
	int				floor_color;
	char			**textures_img;
	t_coord			p_coord;
	t_textures		*textures;
	mlx_t			*mlx;
	mlx_image_t		*map_img;
	mlx_image_t		*player_img;
	mlx_texture_t	*walln;
	mlx_texture_t	*walls;
	mlx_texture_t	*wallw;
	mlx_texture_t	*walle;
	double			ray_inc;
	double			fov_angle;
	int				mouse_x;
	int				mouse_y;
}					t_cub;

int					rgba(int r, int g, int b, float t);
#endif
