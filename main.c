/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:42:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/18 20:52:28 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <drawing.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 720
#define CHECKER_W 50
#define MVT_SPEED 5

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

void put_player(t_vars *vars)
{
	t_player	*player = NULL;
	t_vect2d	forward_scaled;
	int			i;
	int			j;
	int 		plane_half = vars->view_plane_width / 2;

	player = &vars->player;
	forward_scaled = vector_scale(&player->dir, vars->dist_to_plane);
	t_vect2d side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};

	// Look Rays
	for (i = -plane_half; i <= plane_half; ++i)
	{
		t_vect2d var_side = (t_vect2d){i * side_dir.x, i * side_dir.y};
		t_vect2d ray_end = vector_add(&forward_scaled, &var_side);
		draw_line(vars, 
			   player->pos, 
			   vector_add(&player->pos, &ray_end), 
			   0x5050FFFF
		);
	}

	// Player dot
	for (i = (int)player->pos.x - 1; i <= (int)player->pos.x + 2; ++i)
		for (j = (int)player->pos.y - 1; j <= (int)player->pos.y + 2; ++j)
			prot_put_pixel(vars->img, i, j, 0x50FF50FF);
}

void checker(t_vars* vars)
{
	uint32_t color;

	for (uint32_t i = 0; i < vars->img->width; ++i)
	{
		for (uint32_t y = 0; y < vars->img->height; ++y)
		{
			color = (i / CHECKER_W + y / CHECKER_W) % 2 ? 0xFF5050FF : 0x202020FF;
			mlx_put_pixel(vars->img, i, y, color);
		}
	}
}

void	draw_square(t_vars* vars, t_vect2d anchor, int width, uint32_t color)
{
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < width; ++j)
			mlx_put_pixel(vars->img, anchor.x + i, anchor.y + j, color);
}

void draw_map(t_vars *vars)
{
	// puts("HERE");
	for(int i = 0; i < vars->map.height; ++i)
	{
		for(int j = 0; j < vars->map.width; ++j)
		{
			if (vars->map.data[i * vars->map.height + j])
				draw_square(vars, 
					(t_vect2d){j * CHECKER_W, i * CHECKER_W},
					CHECKER_W,
					0xFF50FFFF);
			// printf("%d, ", vars->map.data[i * vars->map.height + j]);
		}
		// printf("\n");
	}
	// printf("-----------\n");
}

void ft_hook(void* v_vars)
{
	t_vars		*vars;
	t_vect2d	input_mvt;

	input_mvt.x = 0;
	input_mvt.y = 0;
    vars = v_vars;
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
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		vars->look_angle -= 0.1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->look_angle += 0.1;
	// View cone
	if (mlx_is_key_down(vars->mlx, MLX_KEY_Y))
		vars->dist_to_plane += 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_H))
		vars->dist_to_plane -= 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_U))
		vars->view_plane_width += 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_J))
		vars->view_plane_width -= 1;

	if (input_mvt.x == input_mvt.y)
	{
		input_mvt.x /= 1.424;
		input_mvt.y /= 1.424;
	}

	// Rotating look
	vars->player.dir = (t_vect2d){cos(-vars->look_angle), sin(-vars->look_angle)};

	// Moving Logic
	t_vect2d forward_move = vector_scale(&vars->player.dir, -input_mvt.y * MVT_SPEED);
	t_vect2d side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};
	t_vect2d side_move = vector_scale(&side_dir, -input_mvt.x * MVT_SPEED);
	t_vect2d movement = vector_add(&forward_move, &side_move);
	vars->player.pos = vector_add(&vars->player.pos, &movement);

	// Drawing Logic
	checker(vars);
	put_player(vars);
	draw_map(vars);
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
	vars->dist_to_plane = 50;
	vars->view_plane_width = 50;
}

int32_t main(int32_t argc, const char* argv[])
{
	(void)argc;
	(void)argv;
	t_vars vars;
	int map[5][5] = {
		{0, 0, 0, 0, 1},
		{0, 1, 1, 1, 1},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1}
	};


	vars.map.data = (int *)map;
	vars.map.width = 5;
	vars.map.height = 5;
	init_vars(&vars);
	// mlx_loop_hook(vars.mlx, ft_checker, &vars);
	checker(&vars);
	mlx_loop_hook(vars.mlx, ft_hook, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}

