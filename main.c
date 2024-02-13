/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:42:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/13 17:39:24 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <structs.h>
#include <maths.h>
#include <drawing.h>
#include <hooks.h>
#include <parse.h>
#include <validation.h>

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

void	do_graphics(t_vars *vars)
{
	player_mvt(vars);
	draw_background(vars);
	draw_wall_stripes(vars);
	draw_foreground(vars);
	draw_minimap(vars, (t_ivect2d){25, 25});
	draw_fps(vars);
}

int	main(int32_t argc, char *argv[])
{
	t_vars	vars;

	// atexit(check);
	if (argc != 2)
		return (ft_putstr_fd("Usage: ./cub3D map.cub\n", 2), -1);
	if (parser(&vars, argv[1]))
		return (-1);
	if (validator(&vars))
		return (-1);
	initialize(&vars);
	install_hooks(&vars);
	mlx_loop(vars.mlx);
	mlx_delete_image(vars.mlx, vars.img);
	mlx_terminate(vars.mlx);
	free_stuff(&vars);
	return (EXIT_SUCCESS);
}
