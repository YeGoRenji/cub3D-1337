/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:05:36 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 18:12:10 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <hooks.h>

int	check_extension(char *name, char *extension)
{
	char	*ext;

	if (!name || !extension)
		return (1);
	ext = ft_strrchr(name, '.');
	if (!ext)
		return (1);
	return (ft_strcmp(ext + 1, extension));
}

int	check_digit_list(char **list)
{
	size_t	index;
	size_t	res;

	res = 0;
	index = 0;
	while (list[index])
		res += ft_isdigit_string(list[index++]);
	return (res);
}

uint32_t	construct_lgbt(char *_r, char *_g, char *_b)
{
	t_color	col;

    if (!_r || !_g || !_b)
		err_and_exit("Weird with rgb values\n");
	col.r = ft_atoi(_r);
	col.g = ft_atoi(_g);
	col.b = ft_atoi(_b);
	if (validate_lgbt(_r, _g, _b) == -1)
		err_and_exit("Invalid rgb color\n");
	return (col.r << 16 | col.g << 8 | col.b);
}

int	validate_lgbt(char *_r, char *_g, char *_b)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	if (ft_strlen(_r) > 3)
		return (-1);
	if (ft_strlen(_g) > 3)
		return (-1);
	if (ft_strlen(_b) > 3)
		return (-1);
	r = ft_atoi(_r);
	g = ft_atoi(_g);
	b = ft_atoi(_b);
	if (r > 0xff)
		return (-1);
	if (g > 0xff)
		return (-1);
	if (b > 0xff)
		return (-1);
	return (0);
}

void	set_where_and_flag(int **where, int **flag, int *w_val, int *f_val)
{
	*where = w_val;
	*flag = f_val;
}
