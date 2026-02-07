#include "app.h"

static uint32_t	side_color(int side)
{
	if (side == 1)
		return ( 0x00AA55 );
	return (0x00FF88);
}

void	raycast_frame(t_app *a)
{
	int	x;

	clear_frame(a, 0x000000);
	for (int y = 0; y < WIN_HEIGHT / 2; y++)
		for (int i = 0; i < WIN_WIDTH; i++)
			put_px(a, i, y, 0x223355);
	for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
		for (int i = 0;i < WIN_WIDTH; i++)
			put_px(a, i, y, 0x332211);

	x = 0;
	while (x < WIN_WIDTH)
	{
		double	camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
		double	raydirx = a->p.dirx + a->p.planex * camera_x;
		double	raydiry = a->a.diry + a->p.planey * camera_x;
	}
}
