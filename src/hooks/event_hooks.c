/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:38:26 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/11 17:47:28 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hooks.h>

void	exit_failure(t_vars *vars)
{
	if (vars->mlx)
		mlx_close_window(vars->mlx);
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	on_loop(void *v_vars)
{
	t_vars	*vars;

	vars = v_vars;
	do_graphics(vars);
}

void	on_resize(int32_t new_width, int32_t new_height, void *param)
{
	t_vars	*vars;

	vars = param;
	mlx_delete_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, new_width, new_height);
	if (!vars->img)
		exit_failure(vars);
	if (mlx_image_to_window(vars->mlx, vars->img, 0, 0) == -1)
		exit_failure(vars);
}

void	on_click(mlx_key_data_t key_data, void *param)
{
	t_vars	*vars;

	vars = param;
	if ((key_data.key == MLX_KEY_SPACE) && key_data.action == MLX_RELEASE)
		vars->light_status = !vars->light_status;
	if (key_data.key == MLX_KEY_LEFT_ALT && key_data.action == MLX_RELEASE)
	{
		vars->mouse_locked = !vars->mouse_locked;
		mlx_set_cursor_mode(vars->mlx, !vars->mouse_locked * MLX_MOUSE_NORMAL
			+ vars->mouse_locked * MLX_MOUSE_HIDDEN);
	}
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window(vars->mlx);
}

void	on_mouse(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_vars	*vars;

	(void)mods;
	vars = param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		vars->light_status = !vars->light_status;
}
