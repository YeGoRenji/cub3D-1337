/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:42:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/06 05:52:40 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <maths.h>
#include <drawing.h>
#include <dlfcn.h>
#include <time.h>

typedef void (*do_graphics_ptr_t)(t_vars* vars);
do_graphics_ptr_t do_graphics_ptr = NULL;
void	*module = NULL;

void hot_reload()
{
	if (module)
		dlclose(module);
	module = NULL;
	system("make lib/lib.so");
	module = dlopen("lib/lib.so", RTLD_NOW);
	do_graphics_ptr = dlsym(module, "do_graphics");
	// system("clear");
	printf("Reloaded !!\n");
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
	// vars->player.dir = (t_vect2d){1, 0};
	vars->look_angle = -M_PI / 2;
	vars->player.pos = (t_vect2d){1.5, 1.5};

	// Fix these values later (in parsing)
	vars->nb_vert_stripes = WIDTH;
	vars->fov = 1;
	vars->mouse.x = 0;
	vars->mouse.y = 0;
	vars->tile_size = TILE_W;
	vars->nletter_tex = load_tex_png("./resources/NLetter.png");
	// vars->wall_tex[NORTH] = load_tex_png("./resources/pics/MyPic.png");
	// vars->wall_tex[EAST] = load_tex_png("./resources/pics/afatimi.png");
	// vars->wall_tex[WEST] = load_tex_png("./resources/pics/rghouzra.png");
	vars->wall_tex[NORTH] = load_tex_png("./resources/wolftex/greybricks.png");
	vars->wall_tex[EAST] = load_tex_png("./resources/wolftex/greybricksCracked.png");
	vars->wall_tex[SOUTH] = load_tex_png("./resources/wolftex/greybricks.png");
	vars->wall_tex[WEST] = load_tex_png("./resources/wolftex/greybricksCracked.png");
	vars->door_tex = load_tex_png("./resources/wolftex/door.png");
	vars->sky_tex = load_tex_png("./resources/AuroraSkyBox.png");
	hot_reload();
}

void ft_loop(void* v_vars)
{
	t_vars	*vars = v_vars;

	if (mlx_is_key_down(vars->mlx, MLX_KEY_R))
		hot_reload();

	do_graphics_ptr(vars);
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

int32_t main(int32_t argc, const char* argv[])
{
	(void)argc;
	(void)argv;
	t_vars vars;
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
	mlx_loop_hook(vars.mlx, ft_loop, &vars);
	mlx_resize_hook(vars.mlx, on_resize, &vars);
	// mlx_mouse_hook(vars.mlx, ft_mouse, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}

