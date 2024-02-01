/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:52:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/01 03:38:39 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

static mlx_texture_t *get_default_tex(void)
{
	static mlx_texture_t	*def_tex;
	uint32_t				x;
	uint32_t				y;

	if (def_tex)
		return (def_tex);
	def_tex = (mlx_texture_t *)malloc(sizeof(mlx_texture_t));
	def_tex->width = 32;
	def_tex->height = 32;
	def_tex->bytes_per_pixel = 4;
	def_tex->pixels = malloc(def_tex->width * def_tex->height * def_tex->bytes_per_pixel);

	y = 0;
	while(y < def_tex->height)
	{
		x = 0;
		while (x < def_tex->width)
		{
			((uint32_t *)def_tex->pixels)[y * def_tex->height + x] = ((x + y) % 2) * 0xFF00FFFF;
			++x;
		}
		++y;
	}

	return (def_tex);
}

mlx_texture_t	*load_tex_png(const char *path)
{
	mlx_texture_t	*tex;
	uint32_t		x;
	uint32_t		y;
	uint32_t		new_pixel;
	uint32_t		color;

	tex = mlx_load_png(path);
	if (!tex)
		return (get_default_tex());
	y = 0;
	while(y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			new_pixel = 0;
			color = ((uint32_t *)tex->pixels)[y * tex->height + x];
			new_pixel |= (color & 0x000000FF) << 24;
			new_pixel |= (color & 0xFF000000) >> 24;
			new_pixel |= (color & 0x00FF0000) >> 8;
			new_pixel |= (color & 0x0000FF00) << 8;
			((uint32_t *)tex->pixels)[y * tex->height + x] = new_pixel;
			++x;
		}
		++y;
	}
	return (tex);
}
