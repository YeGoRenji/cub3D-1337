#include <structs.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 720
#define CHECKER_W 50

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// int abs(int a, int b)
// {
// 	if (a - b >= 0)
// 		return (a - b);
// 	return (b - a);
// }

void ft_checker(t_vars* vars)
{
	uint32_t color;

	for (uint32_t i = 0; i < vars->img->width; ++i)
	{
		for (uint32_t y = 0; y < vars->img->height; ++y)
		{
			color = (i / CHECKER_W + y / CHECKER_W) % 2 ? 0xFF5050FF : 0x202020FF;
			if (abs((int)i - (int)vars->player.pos.x) <= 4 && abs((int)y - (int)vars->player.pos.y) <= 4)
				color = 0x50FF50FF;
			mlx_put_pixel(vars->img, i, y, color);
		}
	}
}

void ft_hook(void* v_vars)
{
	t_vars	*vars;
	double x = 0;
	double y = 0;

    vars = v_vars;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		y -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		y += 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		x -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		x += 5;
	if (x == y)
	{
		x /= 1.424;
		y /= 1.424;
	}
	vars->player.pos.x += x;
	vars->player.pos.y += y;
	ft_checker(vars);
}

void	exit_failure(t_vars *vars)
{
	if (vars->mlx)
		mlx_close_window(vars->mlx);
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	init_vars(t_vars *vars)
{
	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!vars->mlx)
		exit_failure(vars);
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img)
		exit_failure(vars);
	if (mlx_image_to_window(vars->mlx, vars->img, 0, 0) == -1)
		exit_failure(vars);
	// INFO: Remove this
	vars->player.dir = (t_vect2d){1, 0};
	vars->player.pos = (t_vect2d){10, 10};
}

int32_t main(int32_t argc, const char* argv[])
{
	(void)argc;
	(void)argv;
	t_vars vars;

	init_vars(&vars);
	// mlx_loop_hook(vars.mlx, ft_checker, &vars);
	ft_checker(&vars);
	mlx_loop_hook(vars.mlx, ft_hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}

