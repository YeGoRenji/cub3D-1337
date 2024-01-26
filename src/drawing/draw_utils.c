/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:01:52 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/26 19:53:17 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

bool	inside_circle(t_ivect2d pt, t_ivect2d center, int radius)
{
	t_ivect2d	diff;

	diff = (t_ivect2d){pt.x - center.x, pt.y - center.y};
	if (diff.x * diff.x + diff.y * diff.y <= radius * radius)
		return (true);
	return (false);
}

void	clear_screen(t_vars* vars, uint32_t color)
{
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (y < vars->img->height)
	{
		x = 0;
		while (x < vars->img->width)
		{
			prot_put_pixel(vars->img, x, y, color);
			++x;
		}
		++y;
	}
}

void checker(t_vars* vars) // DEBUG
{
	uint32_t	y;
	uint32_t	x;
	uint32_t color;

	y = 0;
	while (y < vars->img->height)
	{
		x = 0;
		while (x < vars->img->width)
		{
			color = (x / vars->tile_size + y / vars->tile_size) % 2 ? TILE_COL_1 : TILE_COL_2;
			prot_put_pixel(vars->img, x, y, color);
			++x;
		}
		++y;
	}
}

void draw_map(t_vars *vars) // DEBUG
{
	for(int i = 0; i < vars->map.height; ++i)
	{
		for(int j = 0; j < vars->map.width; ++j)
		{
			if (vars->map.data[i * vars->map.height + j])
				draw_square(vars,
					(t_vect2d){j * vars->tile_size, i * vars->tile_size},
					vars->tile_size,
					OLD_MAP_2D);
		}
	}
}

