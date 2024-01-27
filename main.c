/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:42:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/27 02:45:10 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <maths.h>
#include <drawing.h>

void debug_vect(t_vect2d *vec, char *name)
{
	printf("%s = (%f, %f)\n", name, vec->x, vec->y);
}

void ft_hook(void* v_vars)
{
	static double old_time = 0;

	t_vars		*vars;
	t_vect2d	input_mvt;

	input_mvt.x = 0;
	input_mvt.y = 0;
    vars = v_vars;
	mlx_get_mouse_pos(vars->mlx, &vars->mouse.x, &vars->mouse.y);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	// Movement
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		input_mvt.y -= 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		input_mvt.y += 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		input_mvt.x -= 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		input_mvt.x += 1;
	// Rotation
	// TODO: check if look_angle doesn't overflow
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		vars->look_angle -= vars->mlx->delta_time * ROT_SPEED;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->look_angle += vars->mlx->delta_time * ROT_SPEED;
	// View cone
	if (mlx_is_key_down(vars->mlx, MLX_KEY_Y))
		vars->nb_vert_stripes += 10;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_H))
		vars->nb_vert_stripes -= 10;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_U))
		vars->fov += 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_J))
		vars->fov -= 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_T))
		vars->tile_size += 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_G))
		vars->tile_size -= 1;

	// if (mlx_is_mouse_down(vars->mlx, mouse_key_t key)
	if (fabs(input_mvt.x) == fabs(input_mvt.y))
	{
		input_mvt.x /= 1.424;
		input_mvt.y /= 1.424;
	}

	vars->tile_size = clamp_value(vars->tile_size, 5, 50);
	vars->nb_vert_stripes = clamp_value(vars->nb_vert_stripes, 42, WIDTH);
	vars->fov = clamp_value(vars->fov, 1, 50);

	// Rotating look
	vars->player.dir = (t_vect2d){cos(-vars->look_angle), sin(-vars->look_angle)};

	// Moving Logic
	t_vect2d forward_move = vector_scale(&vars->player.dir, -input_mvt.y * vars->mlx->delta_time * MVT_SPEED);
	t_vect2d side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};
	t_vect2d side_move = vector_scale(&side_dir, -input_mvt.x * vars->mlx->delta_time * MVT_SPEED);
	t_vect2d movement = vector_add(&forward_move, &side_move);
	vars->player.pos = vector_add(&vars->player.pos, &movement);

	// Drawing Logic
	// checker(vars);
	//draw_map(vars);
	clear_screen(vars, 0x505050FF);
	// put_player(vars);
	draw_wall_stripes(vars);
	mini_map(vars, (t_ivect2d){25, 25});

	// if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_LEFT))
	// 	mouse_ray_test(vars);

	int fps = (int)(1 / vars->mlx->delta_time);
	if (mlx_get_time() - old_time > 0.1)
	{
		printf("fps: %d        nvs: %d        fov: %d        \r" , fps, vars->nb_vert_stripes, vars->fov);
		fflush(stdout);
		old_time = mlx_get_time();
	}
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
	// INFO: get this from parsing
	vars->player.dir = (t_vect2d){1, 0};
	vars->look_angle = 0;
	vars->player.pos = (t_vect2d){1.5, 1.5};

	// Fix these values later
	vars->nb_vert_stripes = WIDTH;
	vars->fov = 1;
	vars->mouse.x = 0;
	vars->mouse.y = 0;
	vars->tile_size = TILE_W;

	// Noice 69
	vars->nig_pic = mlx_load_png("./resources/NLetter.png");
}

int32_t main(int32_t argc, const char* argv[])
{
	(void)argc;
	(void)argv;
	t_vars vars;
	int map[10][10] = {
		{1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	vars.map.data = (int *)map;
	vars.map.width = 10;
	vars.map.height = 10;

	init_vars(&vars);
	// mlx_loop_hook(vars.mlx, ft_checker, &vars);
	mlx_loop_hook(vars.mlx, ft_hook, &vars);
	// mlx_key_hook(mlx_t *mlx, mlx_keyfunc func, void *param)
	// mlx_mouse_hook(vars.mlx, ft_mouse, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}

