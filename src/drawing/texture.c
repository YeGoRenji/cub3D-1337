/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:52:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/14 18:01:49 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

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

static bool	file_exists(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

mlx_texture_t	*load_tex_png(const char *path)
{
	mlx_texture_t	*tex;
	uint32_t		x;
	uint32_t		y;
	uint32_t		color;

	if (!file_exists(path))
		load_img_err(path);
	tex = mlx_load_png(path);
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
