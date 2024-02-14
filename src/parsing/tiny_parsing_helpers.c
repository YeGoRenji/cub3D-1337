/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_parsing_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:43:22 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 17:25:12 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	item_setter_dispatcher(t_map *m, char *where, char *what)
{
	int	res;

	res = 0;
	if (!where || !what)
		return (-1);
	res += (!ft_strncmp(where, "NO", 3))
		+ (!ft_strncmp(where, "SO", 3))
		+ (!ft_strncmp(where, "WE", 3))
		+ (!ft_strncmp(where, "EA", 3))
		+ (!ft_strncmp(where, "DO", 3));
	if (res)
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
	return ((!!map->tex[SOUTH] + !!map->tex[NORTH] + !!map->tex[EAST]
			+ !!map->tex[WEST] + !!map->tex[DOOR_TEX]) == 5);
}

bool	check_colors(t_map *map)
{
	return ((map->colors.ceiling_set + map->colors.floor_set) == 2);
}

bool	map_items_collected(t_map *map)
{
	return (check_textures(map) && check_colors(map));
}
