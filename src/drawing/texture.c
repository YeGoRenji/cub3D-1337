/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:52:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/06 15:20:47 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

static mlx_texture_t	*get_default_tex(void)
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
	// TODO: change to ft_malloc
	def_tex->pixels = malloc(def_tex->width * def_tex->height
			* def_tex->bytes_per_pixel);
	y = 0;
	while (y < def_tex->height)
	{
		x = 0;
		while (x < def_tex->width)
		{
			((uint32_t *)def_tex->pixels)[y * def_tex->width + x]
				= ((x + y) % 2) * 0xFF00FFFF;
			++x;
		}
		++y;
	}
	return (def_tex);
}

static int	big_to_little(int big)
{
	int	little;

	little = 0;
	little |= (big & 0xFF000000) >> 24;
	little |= (big & 0x00FF0000) >> 8;
	little |= (big & 0x0000FF00) << 8;
	little |= (big & 0x000000FF) << 24;
	return (little);
}

mlx_texture_t	*load_tex_png(const char *path)
{
	mlx_texture_t	*tex;
	uint32_t		x;
	uint32_t		y;
	uint32_t		color;

	tex = mlx_load_png(path);
	if (!tex)
		return (get_default_tex());
	y = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			color = ((uint32_t *)tex->pixels)[y * tex->width + x];
			((uint32_t *)tex->pixels)[y * tex->width + x]
				= big_to_little(color);
			++x;
		}
		++y;
	}
	return (tex);
}
