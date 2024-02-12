/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:45:47 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 17:37:36 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <validation.h>

bool	line_space_or_wall(int *line, size_t width, size_t height)
{
	(void)height;
	return ((count(line, width, WALL)
			+ count(line, width, SPACE_IN_MAP)) == width);
}

bool	col_space_or_wall(int *line, size_t width, size_t height)
{
	return ((count_col(line, width, height, WALL)
			+ count_col(line, width, height, SPACE_IN_MAP)) == height);
}

bool	test_set_horizontal(t_map *m, int *first_line, int *last_line)
{
	ll	i;

	i = 0;
	while (i < (ll)m->height
		&& line_space_or_wall(&m->data[i * m->width], m->width, m->height))
		i++;
	if (i >= (ll)m->height)
		return (false);
	*first_line = i;
	i = m->height - 1;
	while (i >= 0
		&& line_space_or_wall(&m->data[i * m->width], m->width, m->height))
		i--;
	*last_line = i;
	if (*first_line > *last_line)
		return (false);
	return (true);
}

bool	test_set_vertical(t_map *m, int *first_col, int *last_col)
{
	ll	i;

	i = 0;
	while (i < (ll)m->width && col_space_or_wall(&m->data[i], m->width, m->height))
		i++;
	if (i >= (ll)m->width)
		return (false);
	*first_col = i;
	i = m->width - 1;
	while (i >= 0 && col_space_or_wall(&m->data[i], m->width, m->height))
		i--;
	*last_col = i;
	if (*first_col > *last_col)
		return (false);
	return (true);
}
