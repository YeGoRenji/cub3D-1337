/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:31:14 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/14 11:26:14 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

static bool	test_collision(t_vars *vars, t_vect2d test)
{
	t_vect2d	next_pos;
	t_ivect2d	next_mapidx;
	t_ivect2d	move_diff;

	next_pos = vec_add(vars->player.pos, test);
	next_mapidx = (t_ivect2d){floor(next_pos.x), floor(next_pos.y)};
	move_diff = (t_ivect2d){next_mapidx.x - floor(vars->player.pos.x),
		next_mapidx.y - floor(vars->player.pos.y)};
	if (abs(move_diff.x) == abs(move_diff.y)
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
	mouse_move = (t_ivect2d){vars->mouse.x - vars->mlx->width / 2, vars->mouse.y
		- vars->mlx->height / 2};
	mlx_set_mouse_pos(vars->mlx, vars->mlx->width / 2, vars->mlx->height / 2);
	vars->player.angle += mouse_move.x * vars->mlx->delta_time * ROT_SPEED / 20;
	vars->pitch -= mouse_move.y * vars->mlx->delta_time * ROT_SPEED * 69;
}

void	player_mvt(t_vars *vars)
{
	t_vect2d	input_mvt;
	t_vect2d	forward_move;
	t_vect2d	side_move;
	t_vect2d	movement;

	if (vars->mouse_locked)
		mouse_mvt(vars);
	get_input_mvt(vars, &input_mvt);
	view_control(vars);
	limit_values(vars);
	vars->player.dir = (t_vect2d){cos(vars->player.angle), sin(vars->player.angle)};
	forward_move = vec_scale(vars->player.dir, -input_mvt.y
			* vars->mlx->delta_time * MVT_SPEED);
	side_move = vec_scale((t_vect2d){vars->player.dir.y, -vars->player.dir.x},
			-input_mvt.x * vars->mlx->delta_time * MVT_SPEED);
	movement = vec_add(forward_move, side_move);
	move_player(vars, &movement);
}
