#include "app.h"

int	main(void)
{
	t_app	a;

	if (!app_init(&a))
		return (1);

	mlx_hook(a.win, 2, 1L << 0, on_key_press, &a);
	mlx_hook(a.win, 3, 1L << 1, on_key_release, &a);
	mlx_hook(a.win, 17, 0, on_destroy, &a);

	mlx_loop_hook(a.mlx, on_loop, &a);
	mlx_loop(a.mlx);
	return (0);
}
