/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_primitives.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:01:30 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/29 17:05:58 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	draw_square(t_vars* vars, t_vect2d anchor, int width, uint32_t color)
{
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < width; ++j)
			prot_put_pixel(vars->img, anchor.x + i, anchor.y + j, color);
}

void	draw_star(t_vars *vars, t_vect2d center, uint32_t color)
{
	int	i;
	int	j;

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

void draw_trig(t_vars *vars, t_vect2d pos, int width, int height, uint32_t color)
{
	double percent;

	for (int y = pos.y; y < pos.y + height; ++y)
	{
		percent = (double)(y - pos.y)/height;
		for (int x = pos.x - percent * width/2; x < pos.x + percent * width/2; ++x)
		{
			prot_put_pixel(vars->img, x, y, color);
		}
	}
}

void draw_circle(t_vars *vars, t_ivect2d center, int radius, uint32_t color)
{
	int start_x = center.x - radius;
	int start_y = center.y - radius;

	for (int y = start_y; y < start_y + 2 * radius; ++y)
		for (int x = start_x; x < start_x + 2 * radius; ++x)
			if (inside_circle((t_ivect2d){x, y}, center, radius))
				prot_put_pixel(vars->img, x, y, color);
}

void draw_texture(t_vars *vars, mlx_texture_t *texture, t_ivect2d pos)
{
	int *pixels = (int *)texture->pixels;

	for (uint32_t y = pos.y; y < pos.y + texture->height; ++y)
	{
		for (uint32_t x = pos.x; x < pos.x + texture->width; ++x)
		{
			uint32_t color = pixels[(y - pos.y) * texture->width + (x - pos.x)];
			color =  (color & (0xFF << 24)) >> 24  | (color << 8);
			if (color & 0xFF)
				prot_put_pixel(vars->img, x, y, color);
		}
	}
}
