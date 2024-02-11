/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 03:19:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/11 17:33:13 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hooks.h>

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

void	view_control(t_vars	*vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		vars->look_angle += vars->mlx->delta_time * ROT_SPEED;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->look_angle -= vars->mlx->delta_time * ROT_SPEED;
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
}

void	limit_values(t_vars *vars)
{
	vars->pitch = clamp_value(vars->pitch, -vars->mlx->height / 2,
			vars->mlx->height / 2);
	vars->look_angle = fmod(vars->look_angle + (vars->look_angle < 0) * (2
				* M_PI), 2 * M_PI);
	vars->tile_size = clamp_value(vars->tile_size, 5, 50);
	vars->nb_vert_stripes = clamp_value(vars->nb_vert_stripes, 42,
			vars->mlx->width);
	vars->fov = clamp_value(vars->fov, 1, 50);
}
