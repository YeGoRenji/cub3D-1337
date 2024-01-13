/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:42:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/13 04:54:43 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <drawing.h>
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

t_vect2d vector_add(t_vect2d *vec1, t_vect2d *vec2)
{
	return (t_vect2d){vec1->x + vec2->x, vec1->y + vec2->y};
}

t_vect2d vector_scale(t_vect2d *vec, double scale)
{
	return (t_vect2d){scale * vec->x, scale * vec->y};
}

void ft_put_player(t_vars *vars)
{
	t_player	*player = NULL;
	t_vect2d	look_vec;
	int			i;
	int			j;

	player = &vars->player;
	look_vec = vector_scale(&player->dir, 50);
	t_vect2d side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};

	// Look Rays
	for (i = -25; i <= 25; ++i)
	{
		t_vect2d var_side = (t_vect2d){i * side_dir.x, i * side_dir.y};
		t_vect2d ray = vector_add(&look_vec, &var_side);
		draw_line(vars, 
			   player->pos, 
			   vector_add(&player->pos, &ray), 
			   0x5050FFFF
		);
	}

	// Player dot
	for (i = (int)player->pos.x - 1; i <= (int)player->pos.x + 2; ++i)
		for (j = (int)player->pos.y - 1; j <= (int)player->pos.y + 2; ++j)
			mlx_put_pixel(vars->img, i, j, 0x50FF50FF);
}

void ft_checker(t_vars* vars)
{
	uint32_t color;

	for (uint32_t i = 0; i < vars->img->width; ++i)
	{
		for (uint32_t y = 0; y < vars->img->height; ++y)
		{
			color = (i / CHECKER_W + y / CHECKER_W) % 2 ? 0xFF5050FF : 0x202020FF;
			// if (abs((int)i - (int)vars->player.pos.x) <= 4 && abs((int)y - (int)vars->player.pos.y) <= 4)
			// 	color = 0x50FF50FF;
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
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		vars->look_angle -= 0.1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		vars->look_angle += 0.1;
	if (x == y)
	{
		x /= 1.424;
		y /= 1.424;
	}

	// Moving Logic
	vars->player.dir = (t_vect2d){cos(-vars->look_angle), sin(-vars->look_angle)};
	t_vect2d forward_move = vector_scale(&vars->player.dir, -y);
	t_vect2d side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};
	t_vect2d side_move = vector_scale(&side_dir, -x);
	t_vect2d movement = vector_add(&forward_move, &side_move);
	vars->player.pos = vector_add(&vars->player.pos, &movement);
	// vars->player.pos.x += x;
	// vars->player.pos.y += y;

	// Rotating look

	// Drawing Logic
	ft_checker(vars);
	ft_put_player(vars);
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
	vars->look_angle = 0;
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

