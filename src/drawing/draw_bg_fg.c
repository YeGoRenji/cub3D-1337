/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 04:23:22 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/13 02:54:02 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	*draw_skybox(void *param)
{
	t_ivect2d				iter;
	int						offset;
	t_ivect2d				tex_pos;
	const t_thread_artist	*art = param;
	const mlx_texture_t		*tex = art->vars->sky_tex;

	offset = tex->width * (art->vars->look_angle / (2 * M_PI));
	iter = art->start;
	while (iter.y < art->end.y)
	{
		while (iter.x < art->end.x)
		{
			tex_pos.y = (tex->height) * (iter.y + art->vars->mlx->height / 2
					- art->vars->pitch) / art->vars->mlx->height;
			tex_pos.y = clamp_value(tex_pos.y, 0, tex->height);
			tex_pos.x = (tex->width) * iter.x / art->vars->mlx->width;
			tex_pos.x = (tex_pos.x + offset) % tex->width;
			prot_put_pixel(art->vars->img, iter.x, iter.y,
				((uint32_t *)tex->pixels)[tex_pos.y * tex->width + tex_pos.x]);
			++iter.x;
		}
		iter = (t_ivect2d){art->start.x, iter.y + 1};
	}
	return (NULL);
}

void	*draw_floor(void *param)
{
	const t_thread_artist	*art = param;
	t_ivect2d				iter;
	double					div;
	const uint32_t			color = art->vars->map.colors.floor << 8;

	iter = art->start;
	div = (double)1 / (art->end.y - art->start.y);
	while (iter.y < art->end.y)
	{
		while (iter.x < art->end.x)
		{
			prot_put_pixel(art->vars->img, iter.x, iter.y, (int)(0xFF * (iter.y
						- art->start.y) * div) | color);
			++iter.x;
		}
		iter = (t_ivect2d){art->start.x, iter.y + 1};
	}
	return (NULL);
}

void	draw_background(t_vars *vars)
{
	split_draw(vars, draw_skybox, (t_ivect2d){vars->mlx->width,
		(vars->mlx->height >> 1) + vars->pitch}, (t_ivect2d){0, 0});
	split_draw(vars, draw_floor, (t_ivect2d){vars->mlx->width,
		(vars->mlx->height >> 1) - vars->pitch}, (t_ivect2d){0,
		(vars->mlx->height >> 1) + vars->pitch});
}

void	*draw_flash_light(void *param)
{
	t_thread_artist	*art;
	t_ivect2d		iter;
	mlx_texture_t	*tex;
	uint32_t		color;
	t_ivect2d		tex_pos;

	art = param;
	tex = ifelse(art->vars->light_status, art->vars->light_on,
			art->vars->light_off);
	iter = art->start;
	while (iter.y < art->end.y)
	{
		while (iter.x < art->end.x)
		{
			tex_pos.y = (tex->height) * iter.y / art->vars->mlx->height;
			tex_pos.x = (tex->width) * iter.x / art->vars->mlx->width;
			color = ((uint32_t *)tex->pixels)[tex_pos.y * tex->width
				+ tex_pos.x];
			if (color & 0xFF)
				prot_put_pixel(art->vars->img, iter.x, iter.y, color);
			++iter.x;
		}
		iter = (t_ivect2d){art->start.x, iter.y + 1};
	}
	return (NULL);
}

void	draw_foreground(t_vars *vars)
{
	t_ivect2d	tex_start;

	tex_start = (t_ivect2d){(1331 * ((double)vars->mlx->width / WIDTH)), 757
		* ((double)vars->mlx->height / HEIGHT)};
	split_draw(vars, draw_flash_light, (t_ivect2d){vars->mlx->width
		- tex_start.x, vars->mlx->height - tex_start.y}, tex_start);
}
