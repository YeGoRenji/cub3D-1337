/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_definitely_not_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:28:25 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 16:32:01 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

int	try_open_file(char *file, char *extension)
{
	if (!file)
		return (-1);
	if (check_extension(file, extension))
	{
		ft_putstr_fd("we only accept .cub files!\n", 2);
		return (-1);
	}
	return (open_file(file));
}
