/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_not_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:55:19 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 11:37:26 by ylyoussf         ###   ########.fr       */
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
			free(line);
			line = get_next_line(fd);
			if (!line)
				break ;
			line[ft_strlen(line) - 1] = 0;
			continue ;
		}
		ptr = ft_split(line, ' ');
		if (!ptr || get_list_len(ptr) == 2)
		{
			if (item_setter_dispatcher(m, ptr[0], ptr[1]) == -1)
				err_and_exit("Invalid Color\n");
		}
		free_stuff(ptr, line);
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
}

int	get_map_items(t_map *m)
{
	char		*line;
	const int	fd = m -> fd;

	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = 0;
	scan_and_dispatch(m, line, fd);
	return (0);
}
