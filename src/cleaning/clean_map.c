/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:19:58 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 21:21:52 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <clean.h>

void	free_lst_map(t_map_data *ptr)
{
	t_map_line	*line;
	t_map_line	*tmp;

	line = ptr -> data;
	while (line)
	{
		tmp = line -> next;
		free(line -> line);
		free(line);
		line = tmp;
	}
	free(ptr);
}

void	destroy_map(t_map *map)
{
	(void)map;
	return ;
}
