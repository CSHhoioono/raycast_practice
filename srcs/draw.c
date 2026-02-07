#include "app.h"

void	put_px(t_app *a, int x, int y, uint32_t color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = a->frame.addr + (y * a->frame.line_len + x * (a->frame.bpp / 8));
	*(uint32_t *)dst = color;
}

void	clear_frame(t_app *a, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_px(a, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_vline(t_app *a, int x, int y0, int y1, uint32_t color)
{
	int y;

	if (y0 < 0)
		y0 = 0;
	if (y1 >= WIN_HEIGHT)
		y1 = WIN_HEIGHT;

	y = y0;
	while(y <= y1)
	{
		put_px(a, x, y, color);
		y++;
	}
}
