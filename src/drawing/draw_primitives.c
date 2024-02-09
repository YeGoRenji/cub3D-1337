/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_primitives.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:01:30 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/09 02:41:18 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	draw_square(t_vars *vars, t_vect2d anchor, int width, uint32_t color)
{
	t_ivect2d	iter;

	iter = (t_ivect2d){0, 0};
	while (iter.y < width)
	{
		while (iter.x < width)
		{
			prot_put_pixel(vars->img, anchor.x + iter.x, anchor.y + iter.y,
				color);
			++iter.x;
		}
		iter = (t_ivect2d){0, iter.y + 1};
	}
}

/*
void	draw_star(t_vars *vars, t_vect2d center, uint32_t color)
{
	int	i;
	int	j;

	// TODO: prolly remove ! this is unused
	for (i = (int)center.x - 1; i <= (int)center.x + 1; ++i)
		for (j = (int)center.y - 1; j <= (int)center.y + 1; ++j)
			prot_put_pixel(vars->img, i, j, color);
	j = center.y;
	for (i = (int)center.x - 2; i <= (int)center.x + 2; ++i)
		prot_put_pixel(vars->img, i, j, color);
	i = center.x;
	for (j = (int)center.y - 2; j <= (int)center.y + 2; ++j)
		prot_put_pixel(vars->img, i, j, color);
}
*/

void	draw_trig(t_vars *vars, t_ivect2d pos, t_ivect2d size, uint32_t color)
{
	double		percent;
	t_ivect2d	iter;

	iter = pos;
	while (iter.y < pos.y + size.y)
	{
		percent = (double)(iter.y - pos.y) / size.y;
		iter.x = pos.x - percent * size.x / 2;
		while (iter.x < pos.x + percent * size.x / 2)
		{
			prot_put_pixel(vars->img, iter.x, iter.y, color);
			++iter.x;
		}
		++iter.y;
	}
}

void	draw_circle(t_vars *vars, t_ivect2d center, int radius, uint32_t color)
{
	t_ivect2d	iter;
	t_ivect2d	start;

	start.x = center.x - radius;
	start.y = center.y - radius;
	iter = start;
	while (iter.y < start.y + 2 * radius)
	{
		while (iter.x < start.x + 2 * radius)
		{
			if (inside_circle(iter, center, radius))
				prot_put_pixel(vars->img, iter.x, iter.y, color);
			++iter.x;
		}
		iter = (t_ivect2d){start.x, iter.y + 1};
	}
}

void	draw_texture(t_vars *vars, mlx_texture_t *texture, t_ivect2d pos)
{
	int			*pixels;
	t_ivect2d	it;
	uint32_t	color;

	pixels = (int *)texture->pixels;
	it = pos;
	while (it.y < pos.y + (int)texture->height)
	{
		while (it.x < pos.x + (int)texture->width)
		{
			color = pixels[(it.y - pos.y) * texture->width + (it.x - pos.x)];
			if (color & 0xFF)
				prot_put_pixel(vars->img, it.x, it.y, color);
			++it.x;
		}
		it = (t_ivect2d){pos.x, it.y + 1};
	}
}
