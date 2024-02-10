/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:42:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/10 18:08:41 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <maths.h>
#include <drawing.h>
#include <dlfcn.h>

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
	mlx_get_mouse_pos(vars->mlx, &vars->mouse.x, &vars->mouse.y);
	mlx_set_cursor_mode(vars->mlx,  MLX_MOUSE_HIDDEN);
	// INFO: get this from parsing
	// vars->player.dir = (t_vect2d){1, 0};
	vars->look_angle = M_PI / 2;
	vars->player.pos = (t_vect2d){1.5, 1.5};

	// Fix these values later (in parsing)
	vars->nb_vert_stripes = WIDTH;
	vars->fov = 1;
	vars->pitch = 0;
	vars->mouse.x = 0;
	vars->mouse.y = 0;
	vars->tile_size = TILE_W;
	vars->nletter_tex = load_tex_png("./resources/NLetter.png");
	vars->wall_tex[NORTH] = load_tex_png("./resources/wolftex/redbricks.png");
	vars->wall_tex[EAST] = load_tex_png("./resources/wolftex/badgeOnRedbricks.png");
	vars->wall_tex[SOUTH] = load_tex_png("./resources/wolftex/redbricks.png");
	vars->wall_tex[WEST] = load_tex_png("./resources/wolftex/eagleOnRedbricks.png");
	vars->door_tex = load_tex_png("./resources/wolftex/door.png");
	vars->sky_tex = load_tex_png("./resources/AuroraSkyBox.png");
	vars->light_status = false;
	vars->light_on = load_tex_png("./resources/FlashLightOn.png");
	vars->light_off = load_tex_png("./resources/FlashLightOff.png");
	vars->mouse_locked = true;
}

void on_loop(void* v_vars)
{
	t_vars	*vars = v_vars;

	do_graphics(vars);
}

void on_resize(int32_t new_width, int32_t new_height, void *param)
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

void on_click(mlx_key_data_t key_data, void *param)
{
	t_vars	*vars;

	vars = param;
	if ((key_data.key == MLX_KEY_SPACE) && key_data.action == MLX_RELEASE)
		vars->light_status = !vars->light_status;
	if (key_data.key == MLX_KEY_LEFT_ALT && key_data.action == MLX_RELEASE)
	{
		vars->mouse_locked = !vars->mouse_locked;
		mlx_set_cursor_mode(vars->mlx, !vars->mouse_locked * MLX_MOUSE_NORMAL + vars->mouse_locked * MLX_MOUSE_HIDDEN);
	}
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window(vars->mlx);
}


void on_mouse(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_vars	*vars;

	(void)mods;
	vars = param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		vars->light_status = !vars->light_status;
}

void	free_tex(mlx_texture_t *tex)
{
	free(tex->pixels);
	free(tex);
}

void	free_stuff(t_vars *vars)
{
	free_tex(vars->sky_tex);
	free_tex(vars->door_tex);
	free_tex(vars->nletter_tex);
	free_tex(vars->wall_tex[NORTH]);
	free_tex(vars->wall_tex[SOUTH]);
	free_tex(vars->wall_tex[EAST]);
	free_tex(vars->wall_tex[WEST]);
	free_tex(vars->light_on);
	free_tex(vars->light_off);
}

void	check(void)
{
	system("leaks cub3D");
}

int32_t main(int32_t argc, const char* argv[])
{
	(void)argc;
	(void)argv;
	t_vars vars;
	atexit(check);
	int map[10][10] = {
		{1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 2, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 2, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 2, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	vars.map.data = (int *)map;
	vars.map.width = 10;
	vars.map.height = 10;

	init_vars(&vars);
	mlx_loop_hook(vars.mlx, on_loop, &vars);
	mlx_resize_hook(vars.mlx, on_resize, &vars);
	mlx_mouse_hook(vars.mlx, on_mouse, &vars);
	mlx_key_hook(vars.mlx, on_click, &vars);
	mlx_loop(vars.mlx);
	mlx_delete_image(vars.mlx, vars.img);
	mlx_terminate(vars.mlx);
	free_stuff(&vars);

	return (EXIT_SUCCESS);
}

