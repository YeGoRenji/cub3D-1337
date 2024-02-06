/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 04:23:22 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/06 05:56:30 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	draw_skybox(t_vars *vars)
{
	t_ivect2d	iter;
	mlx_texture_t *tex = vars->sky_tex;
	uint32_t	color;

	iter = (t_ivect2d){0, 0};
	while (iter.y < vars->mlx->height)
	{
		while (iter.x < vars->mlx->width)
		{
			int y_tex = (tex->height) * iter.y / vars->mlx->height;
			int x_tex = (tex->width) * iter.x / vars->mlx->width;
			x_tex = (int)(x_tex + tex->width * (((int)(vars->look_angle * (180 / M_PI))) % 360) / 360) % tex->width;
			color = ((uint32_t *)tex->pixels)[y_tex * tex->width + x_tex];
			if (iter.y > vars->mlx->height / 2)
				prot_put_pixel(vars->img, iter.x, iter.y, 0xFF * (2 * (double)(iter.y - (double)vars->mlx->height / 2) / vars->mlx->height));
			else
				prot_put_pixel(vars->img, iter.x, iter.y, color);
			++iter.x;
		}
		iter = (t_ivect2d){0, iter.y + 1};
	}
}
