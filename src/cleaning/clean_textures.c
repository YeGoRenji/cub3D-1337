/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:23:52 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 11:44:49 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <clean.h>

void	free_tex(mlx_texture_t *tex)
{
	if (!tex)
		return ;
	free(tex->pixels);
	free(tex);
}

void	free_textures(t_vars *vars)
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

void	free_texture_names(char **texture_names)
{
	int	i;

	i = 0;
	while (i < 5)
		free(texture_names[i++]);
}
