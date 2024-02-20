/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:16:48 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 21:43:20 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	open_file(char *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\n", 2);
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_map	*init_map(char *file)
{
	t_map	*map;

	if (!file)
		return (NULL);
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		err_and_exit("Can't allocate region");
	return (map);
}

int	set_map_colors(t_map *m, char *_obj, char *lgbt_colors)
{
	int		*where;
	int		*f;
	char	**ptr;

	f = NULL;
	where = NULL;
	if (!m || !lgbt_colors || !_obj)
		return (-1);
	if (!ft_strncmp(_obj, "F", 2))
		set_where_and_flag(&where, &f, &m->colors.floor, &m->colors.floor_set);
	else if (!ft_strncmp(_obj, "C", 2))
		set_where_and_flag(&where, &f, &m->colors.ceiling,
			&m->colors.ceiling_set);
	else
		err_and_exit("Invalid surrounding!\n");
	if (*f)
		err_and_exit("Duplicated colors!\n");
	ptr = ft_split(lgbt_colors, ',');
	if (check_digit_list(ptr))
		err_and_exit("Rgb not a numeric value!\n");
	*where = construct_lgbt(ptr[0], ptr[1], ptr[2]);
	*f = (*where != -1);
	return (free_list(ptr), *where);
}

static void	read_and_append(t_map_data *map_data, t_map *m, char *line, int fd)
{
	int		i;

	i = 0;
	while (line && ft_strlen(line))
	{
		append_map_node(map_data, line);
		i++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
	free(line);
	m->height = i;
	map_data->height = i;
}

t_map_data	*read_map(t_map *map)
{
	t_map_data	*map_data;
	char		*line;
	const int	fd = map -> fd;

	map_data = (t_map_data *)ft_calloc(1, sizeof(t_map_data));
	if (!map_data)
		return (NULL);
	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = 0;
	while (line && !ft_strlen(line))
	{
		free(line);
		line = get_next_line(fd);
		if (line)
			line[ft_strlen(line) - 1] = 0;
	}
	read_and_append(map_data, map, line, fd);
	return (map_data);
}
