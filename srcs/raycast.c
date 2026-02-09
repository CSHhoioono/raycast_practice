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
		double	raydiry = a->p.diry + a->p.planey * camera_x;

		int	mapx = (int)a->p.x;
		int	mapy = (int)a->p.y;
		//deltaDist : 한 그리드를 이동하는데 필요한 광선 거리
		double	deltadistx = (raydirx == 0)? 1e30 : fabs(1.0 / raydirx);
		double	deltadisty = (raydiry == 0)? 1e30 : fabs(1.0 / raydiry);

		double	sidedistx;
		double	sidedisty;

		int	stepx;
		int	stepy;

		int	hit = 0;
		int	side = 0;

		// step & 초기 sideDist
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (a->p.x - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - a->p.x) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (a->p.y - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - a->p.y) * deltadisty;
		}

		// DDA: 다음 그리드 경계까지 더 가까운 축으로 한 칸씩 전진
		while (!hit)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (is_wall(mapx, mapy))
				hit = 1;
		}

		// 카메라에 수직인 거리(피쉬아이 보정)
		double	perpwalldist;
		if (side == 0)
			perpwalldist = (mapx - a->p.x + (1 - stepx) / 2.0) / raydirx;
		else
			perpwalldist = (mapy - a->p.y + (1 - stepy) / 2.0) / raydiry;

		int	line_h = (int)(WIN_HEIGHT / perpwalldist);
		int	draw_start = -line_h / 2 + WIN_HEIGHT / 2;
		int	draw_end = line_h / 2 + WIN_HEIGHT / 2;

		draw_vline(a, x, draw_start, draw_end, side_color(side));
		x++;
	}
}
