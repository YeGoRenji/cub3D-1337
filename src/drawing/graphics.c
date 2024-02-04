/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:31:14 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/04 17:46:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	get_input_mvt(t_vars *vars, t_vect2d *input_mvt)
{
	input_mvt->x = 0;
	input_mvt->y = 0;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		input_mvt->y -= 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		input_mvt->y += 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		input_mvt->x -= 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		input_mvt->x += 1;
	if (fabs(input_mvt->x) == fabs(input_mvt->y))
	{
		input_mvt->x /= 1.424;
		input_mvt->y /= 1.424;
	}
}

void	move_player(t_vars *vars, t_vect2d *movement)
{
	// TODO: refactor this garbage
	t_vect2d	test1 = *movement;
	t_vect2d	test2 = (t_vect2d){movement->x, 0};
	t_vect2d	test3 = (t_vect2d){0, movement->y};
	t_vect2d	next_pos;
	t_ivect2d	next_mapidx;
	
	next_pos = vector_add(&vars->player.pos, &test1);
	next_mapidx = (t_ivect2d){floor(next_pos.x), floor(next_pos.y)};
	if (get_map_val(vars, next_mapidx.x, next_mapidx.y) != 1)
	{
		vars->player.pos = next_pos;
		return ;
	}
	next_pos = vector_add(&vars->player.pos, &test2);
	next_mapidx = (t_ivect2d){floor(next_pos.x), floor(next_pos.y)};
	if (get_map_val(vars, next_mapidx.x, next_mapidx.y) != 1)
	{
		vars->player.pos = next_pos;
		return ;
	}
	next_pos = vector_add(&vars->player.pos, &test3);
	next_mapidx = (t_ivect2d){floor(next_pos.x), floor(next_pos.y)};
	if (get_map_val(vars, next_mapidx.x, next_mapidx.y) != 1)
	{
		vars->player.pos = next_pos;
		return ;
	}
}

void player_mvt(t_vars *vars)
{
	t_vect2d	input_mvt;

	// mlx_delete_image(vars->mlx, vars->img);
	// vars->img = mlx_new_image(vars->mlx, vars->mlx->width, vars->mlx->height);
	// if (!vars->img)
	// 	exit(-1);
	mlx_get_mouse_pos(vars->mlx, &vars->mouse.x, &vars->mouse.y);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	// Movement from input
	get_input_mvt(vars, &input_mvt);
	// Rotation
	// TODO: check if look_angle doesn't overflow
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		vars->look_angle += vars->mlx->delta_time * ROT_SPEED;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->look_angle -= vars->mlx->delta_time * ROT_SPEED;
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

	vars->tile_size = clamp_value(vars->tile_size, 5, 50);
	vars->nb_vert_stripes = clamp_value(vars->nb_vert_stripes, 42, vars->mlx->width);
	vars->fov = clamp_value(vars->fov, 1, 50);

	// Rotating look
	vars->player.dir = (t_vect2d){cos(vars->look_angle), sin(vars->look_angle)};

	// Moving Logic
	t_vect2d forward_move = vector_scale(&vars->player.dir, -input_mvt.y * vars->mlx->delta_time * MVT_SPEED);
	t_vect2d side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};
	t_vect2d side_move = vector_scale(&side_dir, -input_mvt.x * vars->mlx->delta_time * MVT_SPEED);
	t_vect2d movement = vector_add(&forward_move, &side_move);
	move_player(vars, &movement);
}

void do_graphics(t_vars* vars)
{

	player_mvt(vars);

	// Drawing Logic
	// checker(vars);
	// draw_map(vars);
	clear_screen(vars, 0x303030FF);
	// put_player(vars);
	draw_wall_stripes(vars);
	mini_map(vars, (t_ivect2d){25, 25});

	// if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_LEFT))
	// 	mouse_ray_test(vars);
	draw_fps(vars);
}
