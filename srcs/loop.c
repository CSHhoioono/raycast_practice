#include "app.h"

static void	move_player(t_app *a)
{
	const double	move_spd = 0.01;
	const double	rot_spd = 0.005;

	double	nx;
	double	ny;

	//ESC
	if (a->key_esc)
		exit(0);

	// 전후 이동: dir 사용
	if (a->key_w)
	{
		nx = a->p.x + a->p.dirx * move_spd;
		ny = a->p.y + a->p.diry * move_spd;
		// y는 고정하고 이동한 x의 값이 범위를 넘어갔는지 확인.
		if (!is_wall((int)nx, (int)a->p.y)) a->p.x = nx;
		// x는 고정하고 이동한 y의 값이 범위를 넘어갔는지 확인.
		if (!is_wall((int)a->p.x, (int)ny)) a->p.y = ny;
	}
	if (a->key_s)
	{
		nx = a->p.x - a->p.dirx * move_spd;
		ny = a->p.y - a->p.diry * move_spd;
		if (!is_wall((int)nx, (int)a->p.y)) a->p.x = nx;
		if (!is_wall((int)a->p.x, (int)ny)) a->p.y = ny;
	}
	if (a->key_d)
	{
		nx = a->p.x + a->p.planex * move_spd;
		ny = a->p.y + a->p.planey * move_spd;
		if (!is_wall((int)nx, (int)a->p.y)) a->p.x = nx;
		if (!is_wall((int)a->p.x, (int)ny)) a->p.y = ny;
	}
	if (a->key_a)
	{
		nx = a->p.x - a->p.planex * move_spd;
		ny = a->p.y - a->p.planey * move_spd;
		if (!is_wall((int)nx, (int)a->p.y)) a->p.x = nx;
		if (!is_wall((int)a->p.x, (int)ny)) a->p.y = ny;
	}
	//mlx와 math의 좌표계는 차이가 있음 그로 인해서 left는 양의 방향이 아닌 음의 방향으로 움직임.
	if (a->key_left || a->key_right)
	{
		double	ang = (a->key_left ? -rot_spd : rot_spd);
		double	old_dirx = a->p.dirx;
		double	old_planex = a->p.planex;

		a->p.dirx = a->p.dirx * cos(ang) - a->p.diry * sin(ang);
		a->p.diry = old_dirx * sin(ang) + a->p.diry * cos(ang);

		a->p.planex = a->p.planex * cos(ang) - a->p.planey * sin(ang);
		a->p.planey = old_planex * sin(ang) + a->p.planey * cos(ang);
	}
}

int	on_loop(t_app *a)
{
	move_player(a);
	raycast_frame(a);
	mlx_put_image_to_window(a->mlx, a->win, a->frame.img, 0, 0);
	return (0);
}
