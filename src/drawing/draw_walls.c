/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:47:12 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/10 19:42:28 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void  draw_stripe(t_vars *vars, t_rayhit *hit, t_ivect2d wlstart, t_ivect2d wlend, int fog, int width)
{
	const int	half_width = width >> 1;
	const int start = clamp_value(wlstart.y, 0, vars->mlx->height - 1);
	const int end = clamp_value(wlend.y, 0, vars->mlx->height - 1);
	t_vect2d	percent;
	const mlx_texture_t *tex = ifelse(hit->hit_what == WALL, vars->wall_tex[hit->side], vars->door_tex);
	t_ivect2d	it;
	// Shadow ??
	if (hit->side == SOUTH || hit->side == WEST)
		fog = clamp_value(fog - 0x69, 0, 0xFF);
	bool in_light;
	percent.x = hit->pos_in_texture;
	it = (t_ivect2d){wlstart.x - half_width, start};
	while (it.y < end)
	{
		in_light = false;
		if (vars->light_status)
			in_light = inside_circle((t_ivect2d){wlstart.x, it.y}, (t_ivect2d){vars->mlx->width >> 1, vars->mlx->height >> 1}, vars->mlx->width >> 2);
		percent.y = (double)(it.y - wlstart.y) / (wlend.y - wlstart.y);
		uint32_t color =  get_pixel(tex, percent.x * tex->width,
							percent.y * tex->height);
		uint8_t new_fog = clamp_value(fog + 0xFF * in_light * (1 - dist_norm((t_ivect2d){wlstart.x, it.y}, (t_ivect2d){vars->mlx->width >> 1, vars->mlx->height >> 1}, vars->mlx->width >> 2)), 0x10, 0xFF);
		color = (color & 0xFFFFFF00) | new_fog;
		while (it.x <= wlstart.x + half_width)
		{
			prot_put_pixel(vars->img, ++it.x, it.y, color);
			++it.x;
		}
		it = (t_ivect2d){wlstart.x - half_width, it.y + 1};
	}
}

void *threaded_wall_stripes(void *params)
{
	t_thread_artist	*art = params;
	t_vect2d	side_dir;
	int			i;
	const int steps = art->vars->mlx->width / art->vars->nb_vert_stripes;
	int64_t fog = 0xFF;

	side_dir = (t_vect2d){art->vars->player.dir.y, -art->vars->player.dir.x};
	for (i = art->start.x; i < art->end.x; i += steps)
	{
		double cameraX = 2 * (i + ((double)WIDTH/2 - (double)art->vars->mlx->width/2)) / (double)(WIDTH) - 1;
		t_vect2d var_side = vec_scale(side_dir, -cameraX * art->vars->fov);
		t_vect2d ray = vec_add(art->vars->player.dir, var_side);
		t_rayhit hit = ray_cast_dda(art->vars, art->vars->player.pos, ray);
		int h = art->vars->mlx->height + 2 * art->vars->pitch;
		int lineHeight = (int)(HEIGHT / (hit.dist * art->vars->fov));

		// calculate lowest and highest pixel to fill in current stripe
		t_ivect2d drawStart = (t_ivect2d){i, -lineHeight / 2 + h / 2};
		t_ivect2d drawEnd = (t_ivect2d){i, lineHeight / 2 + h / 2};

		fog = clamp_value(0xFF + 10 - hit.dist * 20, 0, 0xFF);
		// hit.side ? ((0xFF5050 << 8) | fog) : ((0x50FF50 << 8) | fog)
		draw_stripe(art->vars, &hit, drawStart, drawEnd, fog, steps);
	}
	return (NULL);
}

void draw_wall_stripes(t_vars *vars)
{
	split_draw(vars, threaded_wall_stripes, (t_ivect2d){vars->mlx->width, vars->mlx->height}, (t_ivect2d){0, 0});
}
