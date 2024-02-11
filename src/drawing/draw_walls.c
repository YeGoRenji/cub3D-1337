/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:47:12 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/11 16:53:01 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

static uint8_t	calc_fog(t_vars *vars, t_ivect2d it, t_ivect2d wlstart,
		t_rayhit hit)
{
	const int		min = 0x20;
	bool			in_light;
	uint8_t			fog;
	double			dist_center;
	const t_ivect2d	center = (t_ivect2d){vars->mlx->width >> 1,
		vars->mlx->height >> 1};

	fog = clamp_value(0xFF + 10 - hit.dist * 20, min, 0xFF);
	in_light = false;
	dist_center = 1;
	if (hit.side == SOUTH || hit.side == WEST)
		fog = clamp_value(fog - 0x69, min, 0xFF);
	if (vars->light_status)
		in_light = inside_circle((t_ivect2d){wlstart.x, it.y}, center,
				vars->mlx->width >> 2);
	if (in_light)
		dist_center = dist_norm((t_ivect2d){wlstart.x, it.y}, center,
				vars->mlx->width >> 2);
	fog = clamp_value(fog + 0xFF * in_light * (1 - dist_center), min, 0xFF);
	return (fog);
}

// INFO: Stripe width is in wlend.x
static void	draw_stripe(t_vars *vars, t_rayhit *hit, t_ivect2d wlstart,
	t_ivect2d wlend)
{
	const t_interval	wall_y = (t_interval){clamp_value(wlstart.y, 0,
			vars->mlx->height - 1), clamp_value(wlend.y, 0,
			vars->mlx->height - 1)};
	t_vect2d			percent;
	const mlx_texture_t	*tex = ifelse(hit->hit_what == WALL,
			vars->wall_tex[hit->side], vars->door_tex);
	t_ivect2d			it;
	uint32_t			color;

	percent.x = hit->pos_in_texture;
	it = (t_ivect2d){wlstart.x - (wlend.x >> 1), wall_y.start};
	while (it.y < wall_y.end)
	{
		percent.y = (double)(it.y - wlstart.y) / (wlend.y - wlstart.y);
		color = get_pixel(tex, percent.x * tex->width, percent.y * tex->height);
		color = apply_fog(color, calc_fog(vars, it, wlstart, *hit));
		while (it.x <= wlstart.x + (wlend.x >> 1))
		{
			prot_put_pixel(vars->img, it.x, it.y, color);
			++it.x;
		}
		it = (t_ivect2d){wlstart.x - (wlend.x >> 1), it.y + 1};
	}
}

static void	cast_and_draw(t_vars *vars, double cameraX, int x, int steps)
{
	const int		h = vars->mlx->height + 2 * vars->pitch;
	const t_vect2d	var_side = vec_scale((t_vect2d){vars->player.dir.y,
			-vars->player.dir.x}, -cameraX * vars->fov);
	int				stripe_height;
	t_rayhit		hit;

	hit = ray_cast_dda(vars, vec_add(vars->player.dir, var_side));
	stripe_height = (HEIGHT / (hit.dist * vars->fov));
	draw_stripe(vars, &hit, (t_ivect2d){x, -stripe_height / 2 + h / 2},
		(t_ivect2d){steps, stripe_height / 2 + h / 2});
}

void	*threaded_wall_stripes(void *params)
{
	const t_thread_artist	*art = params;
	const int				steps = art->vars->mlx->width
		/ art->vars->nb_vert_stripes;
	int						x;
	double					camera_x;

	x = art->start.x;
	while (x < art->end.x)
	{
		camera_x = 2 * (x + (double)(WIDTH - art->vars->mlx->width) / 2)
			/ (double)(WIDTH) - 1;
		cast_and_draw(art->vars, camera_x, x, steps);
		x += steps;
	}
	return (NULL);
}

void	draw_wall_stripes(t_vars *vars)
{
	split_draw(vars, threaded_wall_stripes, (t_ivect2d){vars->mlx->width,
		vars->mlx->height}, (t_ivect2d){0, 0});
}
