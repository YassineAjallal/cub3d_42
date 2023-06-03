#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>

#define PI 3.1415926535

float pa,pdx,pdy;
#define FOV_ANGLE (60 * (PI / 180))

int x = 50;
int y = 100;
int view = 200;
void *ptr;
void *win;
void *img;
char map[5][5] = {
	{'1','1','1','1','1'},
	{'1','0','0','0','1'},
	{'1','0','1','0','1'},
	{'1','p','0','0','1'},
	{'1','1','1','1','1'}
};

int ft_s(int s0, int s1)
{
	if (s0 < s1)
		return (1);
	return (-1);
}

void my_line1(int x0, int y0, int x1, int y1, void *mlx, void *win, int color)
{
	int dx;
	int dy;
	int err;
	int e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (dx > dy)
		err = dx / 2;
	else
		err = -dy / 2;
	while (1)
	{
		mlx_pixel_put(mlx, win,x0, y0, color);
		if (map[y0 / 40][x0 / 40] == '1')
			break;
		if ( x0== x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += ft_s(x0, x1);
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += ft_s(y0, y1);
		}
	}

}

void my_line(int x0, int y0, int x1, int y1, void *mlx, void *win, int color)
{
	int dx;
	int dy;
	int px = 0;
	int new_x = 0;
	int err;
	int e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (dx > dy)
		err = dx / 2;
	else
		err = -dy / 2;
	while (1)
	{
		// if (map[y0 / 40][x0 / 40] == '1')
		// 	break;
		mlx_pixel_put(mlx, win,x0, y0, color);
		new_x++;
		if (new_x - px == 10)
		{
			px = new_x;
			my_line1(x, y , x0, y0, mlx, win, 0xffffff);
		}
		if ( x0== x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += ft_s(x0, x1);
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += ft_s(y0, y1);
		}
	}

}

void draw_fov()
{
    float angle = pa - FOV_ANGLE / 2;
    float end_angle = pa + FOV_ANGLE / 2;
	int target_x;
	int target_y;
	int target_x1 = x + cos(angle) * view;
    int target_y1 = y + sin(angle) * view;
	int target_x2 = x + cos(end_angle) * view;
    int target_y2 = y + sin(end_angle) * view;
	my_line(target_x1, target_y1, target_x2, target_y2, ptr, win, 0xFFFFFF);
	my_line(x, y, target_x1, target_y1, ptr, win, 0xFFFFFF);
	my_line(x, y, target_x2, target_y2, ptr, win, 0xFFFFFF);
    // while (angle <= end_angle)
    // {
	// 	target_x = x + cos(angle) * view;
    //     target_y = y + sin(angle) * view;
	// 	my_line(x, y, target_x, target_y, ptr, win, 0xFFFFFF);
    //     angle += 0.01;
    // }
	// angle = pa - FOV_ANGLE / 2;
    // end_angle = pa + FOV_ANGLE / 2;
	// int target_x1 = x + cos(angle) * view;
    // int target_y1 = y + sin(angle) * view;
	// int target_x2 = x + cos(end_angle) * view;
    // int target_y2 = y + sin(end_angle) * view;

	my_line(target_x1, target_y1, target_x2, target_y2, ptr, win, 0xFFFFFF);
}

int	key_hook(int keycode, void *param)
{
	if (keycode == 0)
	{
		pa -= 0.1;
		if(pa < 0)
			pa = 2 * PI;
		pdx = cos(pa);
		pdy = sin(pa);
	}
	if (keycode == 2)
	{
		pa += 0.1;
		if(pa > 2 * PI)
			pa = 0;
		pdx = cos(pa);
		pdy = sin(pa);
	}
	if (keycode == 53)
		exit(0);
	// if(map[y / 50][x / 50] != '1')
	// {
		if (keycode == 123 && map[y / 40][(x - (int)floorf(pdx)) / 40] != '1')
		{
			x -= pdx;
			y -= pdy;
		}
		if (keycode == 124 && map[y / 40][(x + (int)floorf(pdx)) / 40] != '1')
		{
			x += pdx;
			y += pdy;
		}
		if (keycode == 125 && map[(y + (int)floorf(pdy)) / 40][x / 40] != '1')
		{
			x += pdx;
			y += pdy;
		}
		if (keycode == 126 && map[(y - (int)floorf(pdy)) / 40][x / 40] != '1')
		{
			x -= pdx;
			y -= pdy;
		}
	// }
	mlx_clear_window(ptr, win);
	int i = 0;
	int j = 0;
	// mlx_put_image_to_window(ptr, win, img, x, y);
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (map[i][j] == '1')
			{
				mlx_put_image_to_window(ptr, win, img, j * 40, i * 40);
			}
			if (map[i][j] == 'p')
			{
				mlx_pixel_put(ptr, win, x , y, 0xFFFFFF);
			}// mlx_pixel_put(ptr, win, j * 10, i * 10, 0xFFFFFF);
			j++;
		}
		i++;
	}
	draw_fov();
	return (0);
}

int main(int argc, char const *argv[])
{
	ptr = mlx_init();
	int width = 32;
	win = mlx_new_window(ptr, 1280, 720, "Hello World");
	img = mlx_xpm_file_to_image(ptr, "./wall.xpm", &width, &width);
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	int i = 0;
	int j = 0;
	// mlx_put_image_to_window(ptr, win, img, x, y);
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (map[i][j] == '1')
			{
				mlx_put_image_to_window(ptr, win, img, j * 40, i * 40);
			}
			if (map[i][j] == 'p')
			{
				x = j * 40;
				y = i * 40;
				mlx_pixel_put(ptr, win, j * 40, i * 40, 0xFFFFFF);
			}
			j++;
		}
		i++;
	}
	// mlx_pixel_put(ptr, win, x, y, 0xFFFFFF);
	mlx_hook(win, 2, 0, key_hook, NULL);
	mlx_loop(ptr);
	return 0;
}
