#include "app.h"

static int	img_init(t_app *a)
{
	a->frame.img = mlx_new_image(a->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!a->frame.img)
		return (0);
	a->frame.addr = mlx_get_data_addr(a->frame.img, &a->frame.bpp,\
					&a->frame.line_len, &a->frame.endian);
	if (!a->frame.addr)
		return (0);
	return (1);
}

int	app_init(t_app *a)
{
	*a = (t_app){0};

	a->mlx = mlx_init();
	if (!a->mlx)
		return (0);
	
	a->win = mlx_new_window(a->mlx, WIN_WIDTH, WIN_HEIGHT, "raycasting_practice");
	if (!a->win)
		return (0);

	if (!img_init(a))
		return (0);

	if (!load_textures(a))
		return (0);

	// the initial value of player is the point of empty space
	a->p.x = 3.5;
	a->p.y = 3.5;

	a->p.dirx = 1.0;
	a->p.diry = 0.0;

	a->p.planex = 0.0;
	a->p.planey = 0.66;

	return (1);
}
