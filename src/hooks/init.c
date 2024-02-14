/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:01:17 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/14 11:34:53 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hooks.h>

void	init_canvas(t_vars *vars)
{
	vars->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!vars->mlx)
		exit_failure(vars);
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img)
		exit_failure(vars);
	if (mlx_image_to_window(vars->mlx, vars->img, 0, 0) == -1)
		exit_failure(vars);
	mlx_get_mouse_pos(vars->mlx, &vars->mouse.x, &vars->mouse.y);
	mlx_set_cursor_mode(vars->mlx, MLX_MOUSE_HIDDEN);
}

void	init_configs(t_vars *vars)
{
	vars->nb_vert_stripes = WIDTH;
	vars->fov = 1;
	vars->pitch = 0;
	vars->mouse.x = 0;
	vars->mouse.y = 0;
	vars->tile_size = TILE_W;
	vars->wall_tex[NORTH] = load_tex_png(vars, vars->map.tex[NORTH]);
	vars->wall_tex[SOUTH] = load_tex_png(vars, vars->map.tex[SOUTH]);
	vars->wall_tex[EAST] = load_tex_png(vars, vars->map.tex[EAST]);
	vars->wall_tex[WEST] = load_tex_png(vars, vars->map.tex[WEST]);
	vars->door_tex = load_tex_png(vars, vars->map.tex[DOOR_TEX]);
	vars->nletter_tex = load_tex_png(vars, "./resources/NLetter.png");
	vars->sky_tex = load_tex_png(vars, "./resources/AuroraSkyBox.png");
	vars->light_status = false;
	vars->light_on = load_tex_png(vars, "./resources/FlashLightOn.png");
	vars->light_off = load_tex_png(vars, "./resources/FlashLightOff.png");
	vars->mouse_locked = true;
}

void	initialize(t_vars *vars)
{
	init_canvas(vars);
	init_configs(vars);
}
