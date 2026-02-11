#ifndef APP_H
# define APP_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdint.h>
# include "mlx.h"
# include "map.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 450

# define K_ESC 65307
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_LEFT 65361
# define K_RIGHT 65363

typedef struct	s_tex
{
	void	*img;
	char	*addr;
	int	w;
	int	h;
	int	bpp;
	int	line_len;
	int	endian;
}	t_tex;

enum e_tex_id
{
	TEX_N = 0,
	TEX_S = 1,
	TEX_W = 2,
	TEX_E = 3
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}	t_player;

typedef struct	s_app
{
	void	*mlx;
	void	*win;
	t_img	frame;

	t_tex	tex[4];

	t_player	p;

	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_left;
	int	key_right;
	int	key_esc;
}	t_app;

/* init */
int	app_init(t_app *a);

/* texture */
int	load_textures(t_app *a);
void	free_textures(t_app *a);

/* loop */
int	on_loop(t_app *a);

/* draw */
void	clear_frame(t_app *a, uint32_t color);
void	put_px(t_app *a, int x, int y, uint32_t color);
void	draw_vline(t_app *a, int x, int y0, int y1, uint32_t color);

/* raycast */
void	raycast_frame(t_app *a);

/* input */
int	on_key_press(int keycode, t_app *a);
int	on_key_release(int keycode, t_app *a);
int	on_destroy(t_app *a);

/* util */
int	is_wall(int mx, int my);

#endif
