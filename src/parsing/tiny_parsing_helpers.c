/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_parsing_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:43:22 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 11:14:26 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	item_setter_dispatcher(t_map *m, char *where, char *what)
{
	if (!check_textures(m))
		return (set_map_texture(m, where, what));
	else
		return (set_map_colors(m, where, what));
}

int	check_map_items(t_map *map)
{
	if (!check_textures(map))
		err_and_exit("Textures problem\n");
	if (!check_colors(map))
		err_and_exit("Colors problem\n");
	return (0);
}

bool	check_textures(t_map *map)
{
	return ((!!map -> tex[SOUTH]
			+ !!map -> tex[NORTH]
			+ !!map -> tex[EAST]
			+ !!map -> tex[WEST]
			+ !!map -> tex[DOOR_TEX]) == 5);
}

bool	check_colors(t_map *map)
{
	// TODO: check only floor ?
	return ((map -> colors.ceiling_set
			+ map -> colors.floor_set) == 2);
}

bool	map_items_collected(t_map *map)
{
	return (check_textures(map) && check_colors(map));
}
