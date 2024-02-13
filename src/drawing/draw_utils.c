/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:01:52 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/13 14:22:25 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	clear_screen(t_vars *vars, uint32_t color)
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

int32_t	get_pixel(const mlx_texture_t *tex, int x, int y)
{
	if (!(0 <= x && x < (int)tex->width))
		return (0xFF69FFFF);
	if (!(0 <= y && y < (int)tex->height))
		return (0xFF69FFFF);
	return (((uint32_t *)tex->pixels)[y * tex->width + x]);
}

uint32_t	apply_fog(uint32_t color, uint8_t fog)
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	const double	percent = (double)fog / 0xFF;

	r = (color & 0xFF000000) >> 24;
	g = (color & 0x00FF0000) >> 16;
	b = (color & 0x0000FF00) >> 8;
	r *= percent;
	g *= percent;
	b *= percent;
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

void	prot_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	if (!(0 <= x && x < (int)image->width))
		return ;
	if (!(0 <= y && y < (int)image->height))
		return ;
	mlx_put_pixel(image, x, y, color);
}
