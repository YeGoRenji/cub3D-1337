/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:50:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/27 03:22:22 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	put_mini_map_cursor(t_vars *vars, t_vect2d center)
{
	const int half_width = 10;
	const int trig_width = 2 * half_width - 2;
	const int trig_height = 2 * half_width - 2;

	draw_trig(vars, (t_vect2d){center.x + 0.5, center.y  - half_width - 10}, trig_width - 3, trig_height, 0);

	for (int y = -half_width; y < half_width; ++y)
	{
		for (int x = -half_width; x < half_width; ++x)
		{
			if (inside_circle((t_ivect2d){center.x + x, center.y + y}, (t_ivect2d){center.x, center.y}, half_width - 5))
				prot_put_pixel(vars->img, center.x + x, center.y + y, 0xFFFFFFFF);
			else if (inside_circle((t_ivect2d){center.x + x, center.y + y}, (t_ivect2d){center.x, center.y}, half_width - 2))
				prot_put_pixel(vars->img, center.x + x, center.y + y, 0);
		}
	}
	draw_trig(vars, (t_vect2d){center.x + 0.5, center.y - half_width - 3}, trig_width - 6, trig_height - 2, 0xFFFFFFFF);
}


void mini_map(t_vars *vars, t_ivect2d pos)
{
	// TODO: the signs of the vectors are just tweaked bruteforce (UNDERSTAND MORE ?)
	t_vect2d forward = (t_vect2d){vars->player.dir.x, -vars->player.dir.y};
	t_vect2d right = (t_vect2d){-vars->player.dir.y, -vars->player.dir.x};
	t_vect2d center = (t_vect2d){(double)MINI_MAP_WIDTH / 2 + pos.x, (double)MINI_MAP_WIDTH / 2 + pos.y};

	// Testing
	t_vect2d mat_col1 = (t_vect2d){forward.y, -right.y};
	t_vect2d mat_col2 = (t_vect2d){-forward.x, right.x};

	forward = vector_scale(&forward, vars->tile_size);
	right = vector_scale(&right, vars->tile_size);

	forward = vector_add(&forward, &center);
	right = vector_add(&right, &center);

	for (int y = pos.y; y < pos.y + MINI_MAP_WIDTH; ++y)
	{
		for (int x = pos.x; x < pos.x + MINI_MAP_WIDTH; ++x)
		{
			if (inside_circle((t_ivect2d){x, y}, (t_ivect2d){center.x, center.y}, MINI_MAP_WIDTH / 2 - 10))
			{
				t_vect2d coord_rel_center = {x - center.x, y - center.y};
				coord_rel_center = vector_scale(&coord_rel_center, (double)1/vars->tile_size);
				t_vect2d coord_transform = vector_scale(&mat_col1, coord_rel_center.x);
				t_vect2d addit = vector_scale(&mat_col2, coord_rel_center.y);
				coord_transform = vector_add(&coord_transform, &addit);
				t_vect2d map_coord = vector_add(&vars->player.pos, &coord_transform);
				// t_vect2d map_coord = vector_sub(&vars->player.pos, &coord_rel_center);
				if (get_map_val(vars, floor(map_coord.x), floor(map_coord.y)) > 0)
					prot_put_pixel(vars->img, x, y, TILE_COL_1);
				else
					prot_put_pixel(vars->img, x, y, TILE_COL_2);
			}
			else if (inside_circle((t_ivect2d){x, y}, (t_ivect2d){center.x, center.y}, MINI_MAP_WIDTH / 2))
					prot_put_pixel(vars->img, x, y, 0x303030FF);
		}
	}
	// draw_star(vars, center, 0x0000FFFF);
	put_mini_map_cursor(vars, center);
	t_vect2d center_to_n = vector_scale(&vars->player.dir, (double)MINI_MAP_WIDTH / 2 - 5);
	t_ivect2d north_center = (t_ivect2d){center.x - center_to_n.x, center.y + center_to_n.y};
	int n_radius = 20;
	draw_circle(vars, north_center, n_radius, 0);
	draw_texture(vars, vars->nig_pic, (t_ivect2d){north_center.x - n_radius, north_center.y - n_radius});
	// draw_line(vars, center, forward, 0xFF0000FF);
	// draw_line(vars, center, right, 0x0000FFFF);
}
