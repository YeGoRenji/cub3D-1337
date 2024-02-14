/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_not_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:55:19 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 16:36:56 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <clean.h>
#include <hooks.h>

static void	free_stuff(char **ptr, char *line)
{
	free_list(ptr);
	free(line);
}

void	scan_and_dispatch(t_map *m, char *line, int fd)
{
	char	**ptr;

	while (line && !map_items_collected(m))
	{
		if (!ft_strlen(line))
		{
			(free(line), line = NULL);
			line = get_next_line(fd);
			if (!line)
				break ;
			line[ft_strlen(line) - 1] = 0;
			continue ;
		}
		ptr = ft_split(line, ' ');
		if (ptr && *ptr)
			if (get_list_len(ptr) == 2)
			{
				if (item_setter_dispatcher(m, ptr[0], ptr[1]) == -1)
					err_and_exit("Invalid Color\n");
			}
			else
				err_and_exit("Parsing error\n");
		else
			err_and_exit("Parsing error\n");
		free_stuff(ptr, line);
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
	free(line);
}

int	get_map_items(t_map *m)
{
	char		*line;
	const int	fd = m -> fd;

	if (!m)
		return (-1);
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
	scan_and_dispatch(m, line, fd);
	if (!map_items_collected(m))
		err_and_exit("Missing items\n");
	return (0);
}
