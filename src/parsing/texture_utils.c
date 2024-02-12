/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:27:08 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 14:51:36 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <structs.h>

/*
int	get_map_textures(t_map *map)
{
	int	res;

	res = get_textures(map);
	// TODO : might make an error function!, talk with youssef about this
	if (res != 4)
	{
		if (res == -1)
			return (ft_putstr_fd("Erorr: duplicated texture!\n", 2), -1);
		else
			return (ft_putstr_fd("Error: Missing textures!\n", 2), -1);
	}
	return (0);
}
*/

/*
int	get_textures(t_map *m)
{
	char		*line;
	char		**ptr;
	const int	fd = m -> fd;

	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = 0;
	while (line && ft_strlen(line))
	{
		ptr = ft_split(line, ' ');
		if (!ptr || get_list_len(ptr) == 2)
		{
			if (set_map_texture(m, ptr[0], ft_strdup(ptr[1])) == -1)
				return (free_list(ptr),
						free(line)
						, -1);
		}
		free_list(ptr);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
	}
	return (!!m->tex[UP] + !!m->tex[DOWN] + !!m->tex[RIGHT] + !!m->tex[LEFT]);
}
*/
