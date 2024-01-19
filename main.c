/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:42:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/19 19:01:56 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs.h>
#include <drawing.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 720
#define CHECKER_W 50
#define CHECKER_COLOR_1 0xFF8050FF
#define CHECKER_COLOR_2 0x202020FF
#define MAP_WALL_COLOR 0xAA50AAFF

#define MVT_SPEED 5
#define VARNAME(var) #var


int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

double abs_f(double a)
{
	if (a < 0)
		return (-a);
	return (a);
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

double	vector_magnitude(t_vect2d *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y));
}

t_vect2d	vector_normalize(t_vect2d *vec)
{
	double	mag;

	mag = vector_magnitude(vec);
	return ((t_vect2d){
		vec->x / mag,
		vec->y / mag
	});
}

void	draw_star(t_vars *vars, t_vect2d center, uint32_t color)
{
	int	i;
	int	j;

	for (i = (int)center.x - 1; i <= (int)center.x + 1; ++i)
		for (j = (int)center.y - 1; j <= (int)center.y + 1; ++j)
			prot_put_pixel(vars->img, i, j, color);

	j = center.y;
	for (i = (int)center.x - 2; i <= (int)center.x + 2; ++i)
		prot_put_pixel(vars->img, i, j, color);
	i = center.x;
	for (j = (int)center.y - 2; j <= (int)center.y + 2; ++j)
		prot_put_pixel(vars->img, i, j, color);
}

void put_player(t_vars *vars)
{
	t_player	*player = NULL;
	t_vect2d	forward_scaled;
	int			i;
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
	draw_star(vars, player->pos, 0x50FF50FF);
	// for (i = (int)player->pos.x - 1; i <= (int)player->pos.x + 2; ++i)
	// 	for (j = (int)player->pos.y - 1; j <= (int)player->pos.y + 2; ++j)
	// 		prot_put_pixel(vars->img, i, j, 0x50FF50FF);
}

void checker(t_vars* vars)
{
	uint32_t color;

	for (uint32_t i = 0; i < vars->img->width; ++i)
	{
		for (uint32_t y = 0; y < vars->img->height; ++y)
		{
			color = (i / CHECKER_W + y / CHECKER_W) % 2 ? CHECKER_COLOR_1 : CHECKER_COLOR_2;
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
	for(int i = 0; i < vars->map.height; ++i)
	{
		for(int j = 0; j < vars->map.width; ++j)
		{
			if (vars->map.data[i * vars->map.height + j])
				draw_square(vars, 
					(t_vect2d){j * CHECKER_W, i * CHECKER_W},
					CHECKER_W,
					MAP_WALL_COLOR);
		}
	}
}

int get_map_val(t_vars *vars, int i, int j)
{
	if (i < 0 || i >= vars->map.width)
		return 1;
	if (j < 0 || j >= vars->map.height)
		return 1;
	return vars->map.data[j * vars->map.height + i];
}

void debug_vect(t_vect2d *vec, char *name)
{
	printf("%s = (%f, %f)\n", name, vec->x, vec->y);
}

void	ray_intersect_test(t_vars *vars)
{
	t_vect2d	ray;
	t_vect2d	ray_normalized;
	// printf("Mouse here (%d, %d)\n", vars->mouseX, vars->mouseY);
	ray.x = vars->mouseX - vars->player.pos.x;
	ray.y = vars->mouseY - vars->player.pos.y;
	ray_normalized = vector_normalize(&ray);
	ray = vector_scale(&ray_normalized, CHECKER_W);

	printf("-----\n");
	draw_line(vars, vars->player.pos, (t_vect2d){vars->mouseX, vars->mouseY}, 0xFFFFFFFF);
	t_vect2d delta_dist;
	delta_dist.x = ray_normalized.x == 0 ? 1e30 : abs_f(1 / ray_normalized.x);
	delta_dist.y = ray_normalized.y == 0 ? 1e30 : abs_f(1 / ray_normalized.y);

	debug_vect(&delta_dist, VARNAME(delta_dist));

	t_vect2d step;
	step.x = 1 - 2 * (ray.x < 0);
	step.y = 1 - 2 * (ray.y < 0);
	
	debug_vect(&step, VARNAME(step));

	t_vect2d side_dist;

	double pos_x = vars->player.pos.x / CHECKER_W;
	double pos_y = vars->player.pos.y / CHECKER_W;

	int map_x = (int)(vars->player.pos.x / CHECKER_W);
	int map_y = (int)(vars->player.pos.y / CHECKER_W);


	if (ray.x < 0)
		side_dist.x = (pos_x - map_x) * delta_dist.x;
	else
		side_dist.x = (1 - (pos_x - map_x)) * delta_dist.x;
	if (ray.y < 0)
		side_dist.y = (pos_y -  map_y) * delta_dist.y;
	else
		side_dist.y = (1 - (pos_y - map_y)) * delta_dist.y;

	debug_vect(&side_dist, VARNAME(side_dist));

	t_vect2d first_side_x = vector_scale(&ray_normalized, side_dist.x);
	first_side_x = vector_scale(&first_side_x, CHECKER_W);
	draw_star(vars, vector_add(&vars->player.pos, &first_side_x), 0xFFFF00FF);

	t_vect2d first_side_y = vector_scale(&ray_normalized, side_dist.y);
	first_side_y = vector_scale(&first_side_y, CHECKER_W);
	draw_star(vars, vector_add(&vars->player.pos, &first_side_y), 0x00FFFFFF);

	int iterations = 8;
	int i = 0;
	while (i < iterations)
  	{
		int hit = 0;
		int is_x = 0;
		// Fix: Hitpoint is delayed maybe
		// jump to next map square, either in x-direction, or in y-direction
		if (side_dist.x < side_dist.y)
		{
			is_x = 1;
			side_dist.x += delta_dist.x;
			map_x += step.x;
			// side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map_y += step.y;
			// side = 1;
		}
		//Check if ray has hit a wall
		hit = get_map_val(vars, map_x, map_y) > 0;

		if (is_x)
		{
			if (hit)
				printf("X:Hit wall at (%d, %d) in iteration %d\n", map_x, map_y, i);
			t_vect2d visual_next_side_x = vector_scale(&ray_normalized, side_dist.x);
			visual_next_side_x = vector_scale(&visual_next_side_x, CHECKER_W);
			draw_star(vars, vector_add(&vars->player.pos, &visual_next_side_x), hit ? 0xFF0000FF : 0xFFFF00FF);
		}
		else
		{
			if (hit)
				printf("Y:Hit wall at (%d, %d) in iteration %d\n", map_x, map_y, i);
			t_vect2d visual_next_side_y = vector_scale(&ray_normalized, side_dist.y);
			visual_next_side_y = vector_scale(&visual_next_side_y, CHECKER_W);
			draw_star(vars, vector_add(&vars->player.pos, &visual_next_side_y), hit ? 0xFF0000FF : 0x00FFFFFF);
		}
		++i;
	}

	// draw_line(vars, vars->player.pos, vector_add(&vars->player.pos, &first_side_x), 0xFFFF00FF);
}

void ft_hook(void* v_vars)
{
	t_vars		*vars;
	t_vect2d	input_mvt;
	
	input_mvt.x = 0;
	input_mvt.y = 0;
    vars = v_vars;
	mlx_get_mouse_pos(vars->mlx, &vars->mouseX, &vars->mouseY);
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
	// TODO : Make speed independent of CPU speed (use deltaTime)
	t_vect2d forward_move = vector_scale(&vars->player.dir, -input_mvt.y * MVT_SPEED);
	t_vect2d side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};
	t_vect2d side_move = vector_scale(&side_dir, -input_mvt.x * MVT_SPEED);
	t_vect2d movement = vector_add(&forward_move, &side_move);
	vars->player.pos = vector_add(&vars->player.pos, &movement);

	// Drawing Logic
	checker(vars);
	put_player(vars);
	draw_map(vars);
	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_LEFT))
		ray_intersect_test(vars);
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
	// INFO: get this from data
	vars->player.dir = (t_vect2d){1, 0};
	vars->look_angle = 0;
	vars->player.pos = (t_vect2d){10, 10};

	// Fix these values later
	vars->dist_to_plane = 50;
	vars->view_plane_width = 50;
	vars->mouseX = 0;
	vars->mouseY = 0;
}

int32_t main(int32_t argc, const char* argv[])
{
	(void)argc;
	(void)argv;
	t_vars vars;
	int map[5][5] = {
		{0, 0, 0, 0, 1},
		{0, 0, 1, 0, 1},
		{0, 0, 1, 0, 1},
		{0, 0, 1, 1, 1},
		{0, 0, 0, 0, 1}
	};


	vars.map.data = (int *)map;
	vars.map.width = 5;
	vars.map.height = 5;
	init_vars(&vars);
	// mlx_loop_hook(vars.mlx, ft_checker, &vars);
	checker(&vars);
	mlx_loop_hook(vars.mlx, ft_hook, &vars);
	// mlx_mouse_hook(vars.mlx, ft_mouse, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}

