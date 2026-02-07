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

/* loop */
int	on_loop(t_app *a);

/* draw */
void	clear_fram(t_app *a, uint32_t color);
void	put_px(t_app *a, int x, int y, uint32_t color);
void	draw_vline(t_app *a, int x, int y0, int y1, uint32_t color);

/* raycast */
void	raycast_frame(t_app *a);

/* input */
int	on_key_press(int keycode, t_app *a);
int	in_key_release(int keycode, t_app *a);
int	on_destroy(t_app *a);

/* util */
int	is_wall(int mx, int my);

#endif
