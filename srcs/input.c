#include "app.h"

static void	set_key(int keycode, int down, t_app *a)
{
	if (keycode == K_ESC) a->key_esc = down;
	if (keycode == K_W) a->key_w = down;
	if (keycode == K_A) a->key_a = down;
	if (keycode == K_S) a->key_s = down;
	if (keycode == K_D) a->key_d = down;
	if (keycode == K_LEFT) a->key_left = down;
	if (keycode == K_RIGHT) a->key_right = down;
}

int	on_key_press(int keycode, t_app *a)
{
	set_key(keycode, 1, a);
	return (0);
}

int on_key_release(int keycode, t_app *a)
{
	set_key(keycode, 0, a);
	return (0);
}

int	on_destroy(t_app *a)
{
	free_textures(a);
	exit(0);
	return (0);
}
