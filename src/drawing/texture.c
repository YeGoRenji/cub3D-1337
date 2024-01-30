/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:52:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/30 17:41:00 by ylyoussf         ###   ########.fr       */
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

	tex = mlx_load_png(path);
	if (!tex)
		return (get_default_tex());
	return (tex);
}
