#include "app.h"

static int	load_one(t_app *a, t_tex *t, const char *path)
{
	t->img = mlx_xpm_file_to_image(a->mlx, (char *)path, &t->w, &t->h);
	if (!t->img)
		return (0);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
	if (!t->addr)
		return (0);
	return (1);
}

void	free_textures(t_app *a)
{
	for (int i = 0; i < 4; i++)
	{
		if (a->tex[i].img)
			mlx_destroy_image(a->mlx, a->tex[i].img);
		a->tex[i] = (t_tex){0};
	}
}

int	load_textures(t_app *a)
{
	if (!load_one(a, &a->tex[TEX_N], "textures/north.xpm")) return (0);
	if (!load_one(a, &a->tex[TEX_S], "textures/south.xpm")) return (0);
	if (!load_one(a, &a->tex[TEX_W], "textures/west.xpm")) return (0);
	if (!load_one(a, &a->tex[TEX_E], "textures/east.xpm")) return (0);
	return (1);
}
