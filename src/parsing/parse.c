/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 10:52:35 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <parse.h>
#include <clean.h>

int	parser(t_vars *vars, char *file)
{
	t_map	*map;

	map = init_map(file);
	if (!map)
		return (-1);
	map->fd = try_open_file(file, "cub");
	if (map->fd < 0)
		return (free(map), -1);
	if (get_map_parts(map))
		return (-1);
	vars->map = *map;
	free(map);
	return (0);
}

int	get_map_parts(t_map *map)
{
	t_map_data	*lst_map;
	int			res;

	if (!map)
		return (-1);
	res = get_map_items(map);
	if (res == -1)
		return (-1);
	if (check_map_items(map) == -1)
		return (-1);
	lst_map = read_map(map);
	if (!lst_map)
		err_and_exit("Error: while reading the map\n");
	map->data = consume_map(lst_map);
	if (map->data == NULL)
		err_and_exit("Error: while consuming the map\n");
	map->width = lst_map->width;
	free_lst_map(lst_map);
	return (0);
}

int	convert_map_char(char c)
{
	int	res;

	res = 0;
	if (c == ' ')
		res = SPACE_IN_MAP;
	else if (c == 'D')
		res = DOOR;
	else if (c == '0')
		res = 0;
	else if (c == '1')
		res = 1;
	else if (c == 'N')
		res = NORTH_IN_MAP;
	else if (c == 'S')
		res = SOUTH_IN_MAP;
	else if (c == 'W')
		res = WEST_IN_MAP;
	else if (c == 'E')
		res = EAST_IN_MAP;
	else
		res = -1;
	return (res);
}
