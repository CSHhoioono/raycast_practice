#include "app.h"

static	uint32_t	tex_get_px(t_tex *t, int x, int y)
{
	char	*dst;

	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x >= t->w) x = t->w - 1;
	if (y >= t->h) y = t->h - 1;
	dst = t->addr + (y * t->line_len + x * (t->bpp / 8));
	return (*(uint32_t *) dst);
}

static int	pick_wall_tex(int side, double raydirx, double raydiry)
{
	/* side == 0: x축 경계를 넘음 -> 동/서 벽
		side == 1: y축 경계를 넘음 -> 남/북 벽 */
	if (side == 0)
		return (raydirx > 0 ? TEX_W : TEX_E);
	else
		return (raydiry > 0 ? TEX_N : TEX_S);
}

static void	draw_textured_wall(t_app *a, int x, int draw_start, int draw_end,\
		int tex_id, int tex_x, double perpwalldist)
{
	t_tex	*t = &a->tex[tex_id];

	// 벽 높이에 맞춰 y 샘플링 스텝
	double	line_h = (double)(draw_end - draw_start + 1);
	double	step = (double)t->h / line_h;

	// 화면 y=draw_start가 텍스쳐 y 어디서 시작하는지
	double	tex_pos = 0.0;
	(void)perpwalldist;
	
	for (int y = draw_start; y <= draw_end; y++)
	{
		int tex_y = (int)tex_pos;
		uint32_t c = tex_get_px(t, tex_x, tex_y);
		put_px(a, x, y, c);
		tex_pos += step;
	}
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

		if (perpwalldist < 0.2)
			perpwalldist = 0.2;

		int	line_h = (int)(WIN_HEIGHT / perpwalldist);
		int	draw_start = -line_h / 2 + WIN_HEIGHT / 2;
		int	draw_end = line_h / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

		int	tex_id = pick_wall_tex(side, raydirx, raydiry);
		t_tex	*t = &a->tex[tex_id];

		double	wall_x;
		if (side == 0)
			wall_x = a->p.y + perpwalldist * raydiry;
		else
			wall_x = a->p.x + perpwalldist * raydirx;
		wall_x -= floor(wall_x);

		int	tex_x = (int)(wall_x * (double)t->w);

		// 텍스처 좌우 뒤집기
		// 레이가 어느 방향에서 맞는지에 따라  텍스처가 거울처럼 보일 수 있음
		if (side == 0 && raydirx > 0) tex_x = t->w - tex_x - 1;
		if (side == 1 && raydiry < 0) tex_x = t->w - tex_x - 1;

		draw_textured_wall(a, x, draw_start, draw_end, tex_id, tex_x, perpwalldist);
		x++;
	}
}
