/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:01:27 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 17:53:43 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <validation.h>

int	validator(t_vars *vars)
{
	t_map	*map;

	map = &vars->map;
	if (check_for_invalid_characters(map))
		return (ft_putstr_fd("Error\nfound weird chars in map!\n", \
			2), 1);
	if (count_players(map) != 1)
		return (ft_putstr_fd("Error\nThere has to be one player on the map\n", \
			2), 1);
	register_player_pos(vars, map);
	if (validate_map(map) == -1)
		return (ft_putstr_fd("Error\nInvalid map\n", \
			2), 1);
	return (0);
}

bool	zero_or_one(t_map *map, int x, int y)
{
	int	val;

	if (x < 0 || x >= (ll)map->width)
		return (false);
	if (y < 0 || y >= (ll)map->height)
		return (false);
	val = map->data[y * map->width + x];
	return (val == 1 || val == 0);
}

bool	check_neighbours_binary(t_map *map, t_ivect2d pt)
{
	// TODO: add bonus characters
	if (map->data[(pt.y) * map->width + (pt.x)] == WALL)
		return (true);
	if (map->data[(pt.y) * map->width + (pt.x)] == SPACE_IN_MAP)
		return (true);
	if (!zero_or_one(map, (pt.x), (pt.y - 1)))
		return (false);
	if (!zero_or_one(map, (pt.x), (pt.y + 1)))
		return (false);
	if (!zero_or_one(map, (pt.x - 1), (pt.y)))
		return (false);
	if (!zero_or_one(map, (pt.x + 1), (pt.y)))
		return (false);
	return (true);
}

bool	test_middle_part(t_map *map, t_ivect2d start, size_t w, size_t h)
{
	size_t	x;
	size_t	y;

	y = start.y;
	while (y < start.y + h)
	{
		x = start.x;
		while (map->data[y * map->width + x] == SPACE_IN_MAP && x < start.x + w)
			x++;
		while (map->data[y * map->width + x] == WALL && x < start.x + w)
			x++;
		while (x < start.x + w)
		{
			if (!check_neighbours_binary(map, (t_ivector){x, y}))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

int	validate_map(t_map *map)
{
	int		first_line;
	int		last_line;
	int		first_col;
	int		last_col;

	if (!test_set_horizontal(map, &first_line, &last_line))
		return (-1);
	if (!test_set_vertical(map, &first_col, &last_col))
		return (-1);
	if (!test_middle_part(map, (t_ivector){first_col, first_line},
		last_col - first_col + 1, last_line - first_line + 1))
		return (-1);
	return (0);
}
