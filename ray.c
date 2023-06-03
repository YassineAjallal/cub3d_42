#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>

#define PI 3.1415926535

float pa,pdx,pdy;
#define FOV_ANGLE (60 * (PI / 180))

int x = 50;
int y = 100;
int view = 10;
void *ptr;
void *win;
void *img;

void	draw_look_at(void *img, int line_len, int bpp, int x, int y, float pa, int view)
{
	float px = x + cos(pa) * view;
	float py = y + sin(pa) * view;
	int index = line_len * (int)py + (int)px * (bpp / 8);
	img_pix_put((t_img *)img, (int)px, (int)py, 0x00FF0000);
}

int	key_hook(int keycode, void *param)
{
	printf("%f\n", pa);
	if (keycode == 0)
	{
		pa -= 0.1;
		if(pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (keycode == 2)
	{
		pa += 0.1;
		if(pa > 2 * PI)
			pa += 0;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (keycode == 53)
		exit(0);
	if (keycode == 123)
	{
		x -= pdx;
		y -= pdy;
	}
	if (keycode == 124)
	{
		x += pdx;
		y += pdy;
	}
	if (keycode == 125)
	{
		x += pdx;
		y += pdy;
	}
	if (keycode == 126)
	{
		x -= pdx;
		y -= pdy;
	}
	mlx_clear_window(ptr, win);
	mlx_put_image_to_window(ptr, win, img, x, y);
	return (0);
}

int main(int argc, char const *argv[])
{
	ptr = mlx_init();
	int width = 32;
	win = mlx_new_window(ptr, 1280, 720, "Hello World");
	img = mlx_xpm_file_to_image(ptr, "./Shoot.xpm", &width, &width);
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	draw_look_at(img, 1280 * 4, 32, x, y, pa, view);
	mlx_put_image_to_window(ptr, win, img, x, y);
	mlx_hook(win, 2, 0, key_hook, NULL);
	mlx_loop(ptr);
	return 0;
}
