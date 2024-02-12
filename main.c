/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:42:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/12 18:02:13 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <maths.h>
#include <drawing.h>
#include <hooks.h>
#include <parse.h>
#include <validation.h>

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

	vars -> wall_tex[NORTH] = load_tex_png(vars -> map.tex[NORTH]);
	vars -> wall_tex[SOUTH] = load_tex_png(vars -> map.tex[SOUTH]);
	vars -> wall_tex[EAST] = load_tex_png(vars -> map.tex[EAST]);
	vars -> wall_tex[WEST] = load_tex_png(vars -> map.tex[WEST]);

	vars->door_tex = load_tex_png("./resources/wolftex/door.png");
	vars->sky_tex = load_tex_png("./resources/AuroraSkyBox.png");
	vars->light_status = false;
	vars->light_on = load_tex_png("./resources/FlashLightOn.png");
	vars->light_off = load_tex_png("./resources/FlashLightOff.png");
	vars->mouse_locked = true;
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
	// system("leaks cub3D");
}

void	do_graphics(t_vars *vars)
{
	player_mvt(vars);
	draw_background(vars);
	draw_wall_stripes(vars);
	draw_foreground(vars);
	draw_minimap(vars, (t_ivect2d){25, 25});
	draw_fps(vars);
}

int32_t main(int32_t argc, char* argv[])
{
	(void)argc;
	(void)argv;
	t_vars vars;
	atexit(check);
	if (argc != 2)
		return (ft_putstr_fd("Usage: ./cub3D map.cub\n", 2), -1);
	if (parser(&vars, argv[1]))
		return (-1);
	if (validator(&vars))
		return (-1);
	// if (init_player_data(&vars))
	// 	return (ft_putstr_fd("Error: could not initiate player data\n", 2), -1);
	init_vars(&vars);
	// vars.map.data = (int *)map;
	// vars.map.width = 10;
	// vars.map.height = 10;
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

