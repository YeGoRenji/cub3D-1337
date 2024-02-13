/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:52:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/13 20:48:37 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

mlx_texture_t	*get_default_tex(void)
{
	static mlx_texture_t	def_tex;
	t_ivect2d				it;
	// TODO: free or get rid of this func
	if (def_tex.pixels)
		return (&def_tex);
	def_tex.width = 32;
	def_tex.height = 32;
	def_tex.bytes_per_pixel = 4;
	// TODO: change to ft_malloc
	def_tex.pixels = malloc(def_tex.width * def_tex.height
			* def_tex.bytes_per_pixel);
	it.y = 0;
	while (it.y < (int)def_tex.height)
	{
		it.x = 0;
		while (it.x < (int)def_tex.width)
		{
			((uint32_t *)def_tex.pixels)[it.y * def_tex.width + it.x]
				= ((it.x + it.y) % 2) * 0xFF00FFFF;
			++it.x;
		}
		++it.y;
	}
	return (&def_tex);
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

static bool	file_exists(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

mlx_texture_t	*load_tex_png(t_vars *vars, const char *path, char *err_msg)
{
	mlx_texture_t	*tex;
	uint32_t		x;
	uint32_t		y;
	uint32_t		color;

	if (!file_exists(path))
		(ft_putstr_fd("Error\n", 2), ft_putstr_fd(err_msg, 2), exit_failure(vars));
	tex = mlx_load_png(path);
	// TODO: remove this
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
