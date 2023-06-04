#include "/Users/mkhairou/MLX42/include/MLX42/MLX42.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TILE_SIZE 32;

typedef struct s_map
{

} t_map;


typedef struct t_cub{
	mlx_t 		*mlx;
	mlx_image_t *map;
	mlx_image_t *player;
}s_cub;

s_cub cub;

// void setup()
// {

// }
void	hooks()
{
	if(mlx_is_key_down(cub.mlx,MLX_KEY_ESCAPE))
		exit(0);
	if(mlx_is_key_down(cub.mlx,MLX_KEY_UP))
		cub.player->instances->y -= 3;
	if(mlx_is_key_down(cub.mlx,MLX_KEY_DOWN))
		cub.player->instances->y += 3;
	if(mlx_is_key_down(cub.mlx,MLX_KEY_LEFT))
		cub.player->instances->x -= 3;
	if(mlx_is_key_down(cub.mlx,MLX_KEY_RIGHT))
		cub.player->instances->x += 3;

}

void drw_player()
{
	int radius = 15;
    int centerX = 15;
    int centerY = 15;
	int y;
	int x;

	y = -radius;
    while (y <= radius)
    {
		x = -radius;
        while ( x <= radius)
        {
            if (x * x + y * y <= radius * radius)
            {
                int pixelX = centerX + x;
                int pixelY = centerY + y;
                mlx_put_pixel(cub.player, pixelX, pixelY, 0xFFFFFF);
            }
			x++;
        }
		y++;
    }
}


void	drw_all()
{
	int i = 0;
	int j;

	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			mlx_put_pixel(cub.map,j,i,0xFF1FFF);
			j++;
		}
		i++;
	}
}
void	drw_pixels()
{
	drw_all();
	drw_player();
}

int main()
{
	cub.mlx = mlx_init(1020,540,"CUB3D",0);
	cub.map = mlx_new_image(cub.mlx,1020,540);
	cub.player = mlx_new_image(cub.mlx,50,50);
	mlx_image_to_window(cub.mlx, cub.map, 0,0);
	mlx_image_to_window(cub.mlx, cub.player, 510 - 25,270 - 25);
	mlx_loop_hook(cub.mlx,drw_pixels,NULL);
	mlx_loop_hook(cub.mlx,hooks,NULL);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return(0);
}

