/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:42:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/22 18:28:35 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <maths.h>
#include <drawing.h>

#define WIDTH 1920
#define HEIGHT 1080
#define CHECKER_W 100
#define CHECKER_COLOR_1 0xFF8050FF
#define CHECKER_COLOR_2 0x202020FF
#define MAP_WALL_COLOR 0xAA50AAFF

#define MVT_SPEED 2
#define ROT_SPEED 2
#define VARNAME(var) #var


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

void  draw_stripe(t_vars *vars, int x, int drawStart, int drawEnd, uint32_t color, int width)
{
	int	half_width = width >> 1;

	for (int i = drawStart; i <= drawEnd; ++i)
		for (int j = x - half_width; j <= x + half_width; j++)
			prot_put_pixel(vars->img, j, i, color);
}


t_rayhit ray_cast_dda(t_vars *vars, t_vect2d ray);

void draw_wall_stripes(t_vars *vars)
{
	// t_player	*player = NULL;
	t_vect2d	forward_scaled;
	int			i;

	forward_scaled = vars->player.dir;// vector_scale(&vars->player.dir, vars->dist_to_plane);
	t_vect2d side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};

	// Look Rays
	int steps = WIDTH / vars->nb_vert_stripes;
	for (i = 0; i < WIDTH; i += steps)
	{
		double cameraX = 2 * i / (double)(WIDTH) - 1;// (double)(i + plane_half) / (2 * plane_half);
		
		t_vect2d var_side = (t_vect2d){-cameraX * vars->fov * side_dir.x, -cameraX * vars->fov * side_dir.y};
		t_vect2d ray = vector_add(&forward_scaled, &var_side);
		t_rayhit hit = ray_cast_dda(vars, ray);
		int h = HEIGHT;
		int lineHeight = (int)(h / (hit.dist * vars->fov));

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h) drawEnd = h - 1;

		draw_stripe(vars, i, drawStart, drawEnd, hit.side ? 0xFF5050FF : 0x50FF50FF, steps);

	}
	// for (i = -plane_half; i <= plane_half; ++i)
	// {
	// 	t_vect2d var_side = (t_vect2d){-i * side_dir.x, -i * side_dir.y};
	// 	t_vect2d ray = vector_add(&forward_scaled, &var_side);
	// 	t_rayhit hit = ray_cast_dda(vars, ray);
	// 	int h = HEIGHT;
	// 	int lineHeight = (int)(h / hit.dist);

	// 	// calculate lowest and highest pixel to fill in current stripe
	// 	double cameraX = (double)(i + plane_half) / (2 * plane_half);
	// 	int drawStart = -lineHeight / 2 + h / 2;
	// 	if (drawStart < 0) drawStart = 0;
	// 	int drawEnd = lineHeight / 2 + h / 2;
	// 	if (drawEnd >= h) drawEnd = h - 1;

	// 	draw_stripe(vars, cameraX * WIDTH, drawStart, drawEnd, hit.side ? 0xFF5050FF : 0x50FF50FF);
	// }
}

void put_player(t_vars *vars)
{
	// WARNING : THIS IS OLD need to be synced with ray_cast_dda
	t_vect2d	forward_scaled;
	int			i;
	int 		plane_half = vars->fov / 2;

	t_player visual_player = vars->player;
	visual_player.pos = vector_scale(&visual_player.pos, CHECKER_W);

	forward_scaled = visual_player.dir;
	t_vect2d side_dir = (t_vect2d){visual_player.dir.y, -visual_player.dir.x};

	// Look Rays
	for (i = -plane_half; i <= plane_half; ++i)
	{
		t_vect2d var_side = (t_vect2d){-i * side_dir.x, -i * side_dir.y};
		t_vect2d ray = vector_add(&forward_scaled, &var_side);

		draw_line(vars, 
			   visual_player.pos, 
			   vector_add(&visual_player.pos, &ray), 
			   0x5050FFFF
		);
	}

	// Player dot
	draw_star(vars, visual_player.pos, 0x50FF50FF);
}

void	clear_screen(t_vars* vars, uint32_t color)
{
	for (uint32_t i = 0; i < vars->img->width; ++i)
		for (uint32_t y = 0; y < vars->img->height; ++y)
			mlx_put_pixel(vars->img, i, y, color);
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

t_rayhit ray_cast_dda(t_vars *vars, t_vect2d ray)
{
	t_vect2d	ray_normalized;
	t_vect2d	visual_player_pos;
	// t_vect2d	visual_ray;
	ray_normalized = vector_normalize(&ray);
	// visual_ray = vector_scale(&ray_normalized, CHECKER_W);
	visual_player_pos = vector_scale(&vars->player.pos, CHECKER_W);

	// draw_line(vars, visual_player_pos, vector_add(&visual_player_pos, &visual_ray), 0xFFFFFFFF);
	t_vect2d delta_dist;
	delta_dist.x = ray_normalized.x == 0 ? 1e30 : abs_f(1 / ray_normalized.x);
	delta_dist.y = ray_normalized.y == 0 ? 1e30 : abs_f(1 / ray_normalized.y);

	t_vect2d step;
	step.x = 1 - 2 * (ray.x < 0);
	step.y = 1 - 2 * (ray.y < 0);
	
	t_vect2d side_dist;
	double pos_x = vars->player.pos.x;// / CHECKER_W;
	double pos_y = vars->player.pos.y;// / CHECKER_W;

	t_ivect2d mapidx = (t_ivect2d) {
		(int)(vars->player.pos.x),
		(int)(vars->player.pos.y)
	};


	if (ray.x < 0)
		side_dist.x = (pos_x - mapidx.x) * delta_dist.x;
	else
		side_dist.x = (1 - (pos_x - mapidx.x)) * delta_dist.x;
	if (ray.y < 0)
		side_dist.y = (pos_y -  mapidx.y) * delta_dist.y;
	else
		side_dist.y = (1 - (pos_y - mapidx.y)) * delta_dist.y;

	// t_vect2d first_side_x = vector_scale(&ray_normalized, side_dist.x);
	// first_side_x = vector_scale(&first_side_x, CHECKER_W);
	// draw_star(vars, vector_add(&visual_player_pos, &first_side_x), 0xFFFF00FF);

	// t_vect2d first_side_y = vector_scale(&ray_normalized, side_dist.y);
	// first_side_y = vector_scale(&first_side_y, CHECKER_W);
	// draw_star(vars, vector_add(&visual_player_pos, &first_side_y), 0x00FFFFFF);

	int iterations = 1e9;
	int i = 0;
	int is_x = 0;
	// t_vect2d hit_rel_player;
	int side = 0;
	t_rayhit hit_data;
	while (i < iterations)
  	{
		is_x = 0;
		int hit = 0;
		if (side_dist.x < side_dist.y)
		{
			is_x = 1;
			side_dist.x += delta_dist.x;
			mapidx.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			mapidx.y += step.y;
			side = 1;
		}

		// Check if ray has hit a wall
		hit = get_map_val(vars, mapidx.x, mapidx.y) > 0;

		if (is_x)
		{
			hit_data.dist = side_dist.x - delta_dist.x;
			// hit_rel_player = vector_scale(&ray_normalized, side_dist.x - delta_dist.x);
			// t_vect2d visual_next_side_x = vector_scale(&ray_normalized, side_dist.x - delta_dist.x);
			// visual_next_side_x = vector_scale(&visual_next_side_x, CHECKER_W);
			// draw_star(vars, vector_add(&visual_player_pos, &visual_next_side_x), hit ? 0xFF0000FF : 0xFFFF00FF);
		}
		else
		{
			hit_data.dist = side_dist.y - delta_dist.y;
			// hit_rel_player = vector_scale(&ray_normalized, side_dist.y - delta_dist.y);
			// t_vect2d visual_next_side_y = vector_scale(&ray_normalized, side_dist.y - delta_dist.y);
			// visual_next_side_y = vector_scale(&visual_next_side_y, CHECKER_W);
			// draw_star(vars, vector_add(&visual_player_pos, &visual_next_side_y), hit ? 0xFF0000FF : 0x00FFFFFF);
		}
		if (hit)
			break;
		++i;
	}


	hit_data.where = vector_scale(&ray_normalized, hit_data.dist);
	// t_vect2d visual_hit = vector_scale(&hit_data.where, CHECKER_W);
	hit_data.where = vector_add(&vars->player.pos, &hit_data.where);
	hit_data.side = side;

	// t_vect2d forward_scaled = vector_scale(&vars->player.dir, vars->dist_to_plane);
	// hit_data.dist *=  vector_magnitude(&forward_scaled) / vector_magnitude(&ray);
	hit_data.dist /= vector_magnitude(&ray);

	// draw_star(vars, vector_add(&visual_player_pos, &visual_hit), 0xFF0000FF);
	// draw_line(vars, visual_player_pos, vector_add(&visual_player_pos, &visual_hit), 0xFFFFFFFF);
	return hit_data;
}

void	mouse_ray_test(t_vars *vars) // DEBUG
{
	t_vect2d	ray;
	t_vect2d	ray_normalized;
	t_vect2d	visual_player_pos;
	// printf("Mouse here (%d, %d)\n", vars->mouseX, vars->mouseY);
	ray.x = vars->mouse.x - vars->player.pos.x * CHECKER_W;
	ray.y = vars->mouse.y - vars->player.pos.y * CHECKER_W;
	ray_normalized = vector_normalize(&ray);
	ray = vector_scale(&ray_normalized, CHECKER_W);
	visual_player_pos = vector_scale(&vars->player.pos, CHECKER_W);

	draw_line(vars, visual_player_pos, (t_vect2d){vars->mouse.x, vars->mouse.y}, 0xFFFFFFFF);
	t_vect2d delta_dist;
	delta_dist.x = ray_normalized.x == 0 ? 1e30 : abs_f(1 / ray_normalized.x);
	delta_dist.y = ray_normalized.y == 0 ? 1e30 : abs_f(1 / ray_normalized.y);


	t_vect2d step;
	step.x = 1 - 2 * (ray.x < 0);
	step.y = 1 - 2 * (ray.y < 0);
	

	t_vect2d side_dist;

	double pos_x = vars->player.pos.x;// / CHECKER_W;
	double pos_y = vars->player.pos.y;// / CHECKER_W;

	int map_x = (int)(vars->player.pos.x);// / CHECKER_W);
	int map_y = (int)(vars->player.pos.y);// / CHECKER_W);


	if (ray.x < 0)
		side_dist.x = (pos_x - map_x) * delta_dist.x;
	else
		side_dist.x = (1 - (pos_x - map_x)) * delta_dist.x;
	if (ray.y < 0)
		side_dist.y = (pos_y -  map_y) * delta_dist.y;
	else
		side_dist.y = (1 - (pos_y - map_y)) * delta_dist.y;


	// t_vect2d first_side_x = vector_scale(&ray_normalized, side_dist.x);
	// first_side_x = vector_scale(&first_side_x, CHECKER_W);
	// draw_star(vars, vector_add(&visual_player_pos, &first_side_x), 0xFFFF00FF);

	// t_vect2d first_side_y = vector_scale(&ray_normalized, side_dist.y);
	// first_side_y = vector_scale(&first_side_y, CHECKER_W);
	// draw_star(vars, vector_add(&visual_player_pos, &first_side_y), 0x00FFFFFF);

	int iterations = 8;
	int i = 0;
	int is_x = 0;
	t_vect2d hit_rel_player;
	while (i < iterations)
  	{
		is_x = 0;
		int hit = 0;
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

		// Check if ray has hit a wall
		hit = get_map_val(vars, map_x, map_y) > 0;

		if (is_x)
		{
			hit_rel_player = vector_scale(&ray_normalized, side_dist.x - delta_dist.x);
			// t_vect2d visual_next_side_x = vector_scale(&ray_normalized, side_dist.x - delta_dist.x);
			// visual_next_side_x = vector_scale(&visual_next_side_x, CHECKER_W);
			// draw_star(vars, vector_add(&visual_player_pos, &visual_next_side_x), hit ? 0xFF0000FF : 0xFFFF00FF);
		}
		else
		{
			hit_rel_player = vector_scale(&ray_normalized, side_dist.y - delta_dist.y);
			// t_vect2d visual_next_side_y = vector_scale(&ray_normalized, side_dist.y - delta_dist.y);
			// visual_next_side_y = vector_scale(&visual_next_side_y, CHECKER_W);
			// draw_star(vars, vector_add(&visual_player_pos, &visual_next_side_y), hit ? 0xFF0000FF : 0x00FFFFFF);
		}
		if (hit)
			break;
		++i;
	}

	t_vect2d visual_hit = vector_scale(&hit_rel_player, CHECKER_W);
	draw_star(vars, vector_add(&visual_player_pos, &visual_hit), 0xFF0000FF);
}

int	clamp_value(int val, int min, int max)
{
	if (val < min)
		return min;
	if (val > max)
		return max;
	return val;
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
	// TODO: check if look_angle doesn't overflow also use deltaTime
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
	if (input_mvt.x == input_mvt.y)
	{
		input_mvt.x /= 1.424;
		input_mvt.y /= 1.424;
	}

	vars->nb_vert_stripes = clamp_value(vars->nb_vert_stripes, 2, WIDTH);
	vars->fov = clamp_value(vars->fov, 1, 100);

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
	clear_screen(vars, 0xFFFFFF10);
	// put_player(vars);
	draw_wall_stripes(vars);
	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_LEFT))
		mouse_ray_test(vars);

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
}

int32_t main(int32_t argc, const char* argv[])
{
	(void)argc;
	(void)argv;
	t_vars vars;
	int map[10][10] = {
		{1, 1, 1, 1, 1, 0, 0, 1, 0, 0},
		{1, 0, 0, 0, 1, 0, 0, 1, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 0},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 0},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 0},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0}
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

