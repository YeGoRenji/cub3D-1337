/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 02:44:28 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <parse.h>

int	parser(t_vars *vars, char *file)
{
	t_map	*map;

	map = init_map(file);
	if (!map)
		return (-1);
	map->fd = try_open_file(file, "cub");
	if (map->fd < 0)
		return (-1);
	if (get_map_parts(map))
		return (-1);
	vars->map = *map;
	// TODO : do I need to destroy the map ptr here ???
	return (0);
}

void	display_map(t_map *map)
{
	// TODO : delete this function later!!
	int	*content;
	int w, h;
	int i, j;

	content = map->data;
	w = map->width;
	h = map->height;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			printf("%d, ", content[i * w + j]);
			j++;
		}
		i++;
		puts("");
	}
}

int	set_map_texture(t_map *map, char *text, char *file)
{
	char	fd;
	char	**texture;

	if (!map || !text || !file)
		return (-1);
	if (!ft_strncmp(text, "NO", 3))
		texture = &map->tex[NORTH];
	else if (!ft_strncmp(text, "SO", 3))
		texture = &map->tex[SOUTH];
	else if (!ft_strncmp(text, "WE", 3))
		texture = &map->tex[WEST];
	else if (!ft_strncmp(text, "EA", 3))
		texture = &map->tex[EAST];
	else if (!ft_strncmp(text, "DO", 3))
		texture = &map->tex[DOOR_TEX];
	else
		return (ft_putstr_fd("Error: Wrong map direction\n", 2), -1);
	fd = try_open_file(file, "png");
	if (fd < 0 || *texture)
		return (-1);
	if (texture)
		*texture = ft_strdup(file);
	return (0);
}

int	get_map_parts(t_map *map)
{
	t_map_data	*lst_map;
	int			res;

	if (!map)
		return (-1);
	res = get_map_items(map, set_map_texture, "textures");
	if (res == -1)
		return (-1);
	res = get_map_items(map, set_map_colors, "colors");
	if (res == -1)
		return (-1);
	if (check_map_items(map) == -1)
		return (-1);
	// TODO : make an err_and_exit function
	// TODO : politically correct errors
	/*
	if (res != 2)
	{
		if (res == -1)
			return (ft_putstr_fd("Erorr: duplicated colors!\n", 2), -1);
		else
			return (ft_putstr_fd("Error: Missing colors!\n", 2), -1);
	}
	*/
	lst_map = read_map(map);
	if (!lst_map)
		return (ft_putstr_fd("Error: while reading the map\n", 2), -1);
	map->data = consume_map(lst_map);
	if (map->data == NULL)
		return (ft_putstr_fd("Error: while consuming the map\n", 2), -1);
	map->width = lst_map->width;
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
