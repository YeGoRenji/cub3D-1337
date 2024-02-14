/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:01:27 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 15:12:31 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <validation.h>

size_t	count(const int *line, const int width, int c)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	while (i < width)
		res += line[i++] == c;
	return (res);
}

size_t	count_col(const int *col, const int width, const int height, int c)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	while (i < height)
		res += (col[i++ *width] == c);
	return (res);
}

size_t	count_players(t_map *map)
{
	return (count_object(map, SOUTH_IN_MAP) + count_object(map, NORTH_IN_MAP)
		+ count_object(map, WEST_IN_MAP) + count_object(map, EAST_IN_MAP));
}

size_t	count_object(t_map *map, int object)
{
	size_t	i;
	size_t	res;
	int		width;

	if (!map)
		return (0);
	i = 0;
	res = 0;
	width = map->width;
	while (i < map->height)
		res += count(&map->data[i++ *width], width, object);
	return (res);
}

int	check_for_invalid_characters(t_map *map)
{
	return (count_object(map, -1));
}
