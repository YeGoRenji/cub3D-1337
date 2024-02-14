/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:23:52 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 18:03:55 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <clean.h>

void	free_textures(t_vars *vars)
{
	mlx_delete_texture(vars->sky_tex);
	mlx_delete_texture(vars->door_tex);
	mlx_delete_texture(vars->nletter_tex);
	mlx_delete_texture(vars->wall_tex[NORTH]);
	mlx_delete_texture(vars->wall_tex[SOUTH]);
	mlx_delete_texture(vars->wall_tex[EAST]);
	mlx_delete_texture(vars->wall_tex[WEST]);
	mlx_delete_texture(vars->light_on);
	mlx_delete_texture(vars->light_off);
}

void	free_texture_names(char **texture_names)
{
	int	i;

	i = 0;
	while (i < 5)
		free(texture_names[i++]);
}
