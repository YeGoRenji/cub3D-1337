/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:31:14 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/09 18:13:31 by ylyoussf         ###   ########.fr       */
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

bool	test_collision(t_vars *vars, t_vect2d test)
{
	t_vect2d	next_pos;
	t_ivect2d	next_mapidx;
	t_ivect2d	move_diff;

	next_pos = vec_add(vars->player.pos, test);
	next_mapidx = (t_ivect2d){floor(next_pos.x), floor(next_pos.y)};
	move_diff = (t_ivect2d){next_mapidx.x - floor(vars->player.pos.x), next_mapidx.y - floor(vars->player.pos.y)};
	if (move_diff.x == move_diff.y
		&& get_map_val(vars, next_mapidx.x, floor(vars->player.pos.y)) == WALL
		&& get_map_val(vars, floor(vars->player.pos.x), next_mapidx.y) == WALL)
		return (true);
	if (get_map_val(vars, next_mapidx.x, next_mapidx.y) != WALL)
	{
		vars->player.pos = next_pos;
		return (false);
	}
	return (true);
}

void	move_player(t_vars *vars, t_vect2d *movement)
{
	if (!test_collision(vars, *movement))
		return ;
	if (!test_collision(vars, (t_vect2d){movement->x, 0}))
		return ;
	if (!test_collision(vars, (t_vect2d){0, movement->y}))
		return ;
}

void	mouse_mvt(t_vars *vars)
{
	t_ivect2d	mouse_move;

	mlx_get_mouse_pos(vars->mlx, &vars->mouse.x, &vars->mouse.y);
	mouse_move = (t_ivect2d){vars->mouse.x - vars->mlx->width/2, vars->mouse.y - vars->mlx->height/2};	
	mlx_set_mouse_pos(vars->mlx, vars->mlx->width/2, vars->mlx->height/2);
	vars->look_angle += mouse_move.x * vars->mlx->delta_time * ROT_SPEED / 10;
	vars->pitch -= mouse_move.y * vars->mlx->delta_time * ROT_SPEED * 69;
}

void	player_mvt(t_vars *vars)
{
	t_vect2d	input_mvt;
	// t_ivect2d	old_mouse;
	
	if (vars->mouse_locked)
		mouse_mvt(vars);
	// Movement from input
	get_input_mvt(vars, &input_mvt);
	// Rotation
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
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		vars->pitch += 20;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		vars->pitch -= 20;

	vars->pitch = clamp_value(vars->pitch, -vars->mlx->height/2, vars->mlx->height / 2);

	vars->look_angle = fmod(vars->look_angle + (vars->look_angle < 0) * (2 * M_PI), 2 * M_PI);
	vars->tile_size = clamp_value(vars->tile_size, 5, 50);
	vars->nb_vert_stripes = clamp_value(vars->nb_vert_stripes, 42, vars->mlx->width);
	vars->fov = clamp_value(vars->fov, 1, 50);

	// Rotating look
	vars->player.dir = (t_vect2d){cos(vars->look_angle), sin(vars->look_angle)};

	// Moving Logic
	t_vect2d forward_move = vec_scale(vars->player.dir, -input_mvt.y * vars->mlx->delta_time * MVT_SPEED);
	t_vect2d side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};
	t_vect2d side_move = vec_scale(side_dir, -input_mvt.x * vars->mlx->delta_time * MVT_SPEED);
	t_vect2d movement = vec_add(forward_move, side_move);
	move_player(vars, &movement);
}

void do_graphics(t_vars* vars)
{
	player_mvt(vars);
	// Drawing Logic
	// checker(vars);
	// draw_map(vars);
	// clear_screen(vars, 0x303030FF);
	draw_background(vars);
	// put_player(vars);
	draw_wall_stripes(vars);
	draw_foreground(vars);
	mini_map(vars, (t_ivect2d){25, 25});
	draw_fps(vars);
}
