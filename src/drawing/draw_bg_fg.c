/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 04:23:22 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/06 16:53:47 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	draw_skybox(t_vars *vars)
{
	t_ivect2d		iter;
	mlx_texture_t	*tex = vars->sky_tex;
	uint32_t		color;
	int				offset;

	iter = (t_ivect2d){0, 0};
	offset = tex->width * (((int)(vars->look_angle * (180 / M_PI))) % 360) / 360;
	while (iter.y < vars->mlx->height)
	{
		while (iter.x < vars->mlx->width)
		{
			int y_tex = (tex->height) * iter.y / vars->mlx->height;
			int x_tex = (tex->width) * iter.x / vars->mlx->width;
			x_tex = (int)(x_tex + offset) % tex->width;
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

void	draw_flash_light(t_vars *vars)
{
	t_ivect2d		iter;
	mlx_texture_t	*tex;
	uint32_t		color;

	tex = ifelse(vars->light_status, vars->light_on, vars->light_off);
	iter = (t_ivect2d){0, 0};
	while (iter.y < vars->mlx->height)
	{
		while (iter.x < vars->mlx->width)
		{
			int y_tex = (tex->height) * iter.y / vars->mlx->height;
			int x_tex = (tex->width) * iter.x / vars->mlx->width;
			color = ((uint32_t *)tex->pixels)[y_tex * tex->width + x_tex];
			if (color & 0xFF)
				prot_put_pixel(vars->img, iter.x, iter.y, color);
			++iter.x;
		}
		iter = (t_ivect2d){0, iter.y + 1};
	}

}
