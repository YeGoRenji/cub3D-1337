/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:50:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/09 17:44:47 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	put_mini_map_cursor(t_vars *vars, t_ivect2d center)
{
	const int	half_width = 10;
	const int	trig_width = 2 * half_width - 2;
	const int	trig_height = 2 * half_width - 2;
	t_ivect2d	it;
	t_ivect2d	current;

	draw_trig(vars, (t_ivect2d){center.x + 0.5, center.y - half_width - 10},
		(t_ivect2d){trig_width - 3, trig_height}, 0);
	it.y = -half_width;
	it = (t_ivect2d){-half_width, -half_width};
	while (it.y < half_width)
	{
		while (it.x < half_width)
		{
			current = (t_ivect2d){center.x + it.x, center.y + it.y};
			if (inside_circle(current, center, half_width - 5))
				prot_put_pixel(vars->img, current.x, current.y, 0xFFFFFFFF);
			else if (inside_circle(current, center, half_width - 2))
				prot_put_pixel(vars->img, current.x, current.y, 0x000000FF);
			++it.x;
		}
		it = (t_ivect2d){-half_width, it.y + 1};
	}
	draw_trig(vars, (t_ivect2d){center.x + 0.5, center.y - half_width - 3},
		(t_ivect2d){trig_width - 6, trig_height - 2}, 0xFFFFFFFF);
}

void	mini_map(t_vars *vars, t_ivect2d pos)
{
	// TODO: the signs of the vectors are just tweaked bruteforce (UNDERSTAND MORE ?)
	t_vect2d forward = (t_vect2d){vars->player.dir.x, -vars->player.dir.y};
	t_vect2d right = (t_vect2d){-vars->player.dir.y, -vars->player.dir.x};
	t_vect2d center = (t_vect2d){(double)MINI_MAP_WIDTH / 2 + pos.x, (double)MINI_MAP_WIDTH / 2 + pos.y};

	// Testing
	t_mat2x2 mat_rot = {
		{forward.y, -right.y},
		{-forward.x, right.x}
	};
	// t_vect2d mat_col1 = (t_vect2d){forward.y, -right.y};
	// t_vect2d mat_col2 = (t_vect2d){-forward.x, right.x};

	forward = vec_add(vec_scale(forward, vars->tile_size), center);
	right = vec_add(vec_scale(right, vars->tile_size), center);
	for (int y = pos.y; y < pos.y + MINI_MAP_WIDTH; ++y)
	{
		for (int x = pos.x; x < pos.x + MINI_MAP_WIDTH; ++x)
		{
			if (inside_circle((t_ivect2d){x, y}, (t_ivect2d){center.x, center.y}, MINI_MAP_WIDTH / 2 - 10))
			{
				t_vect2d coord_rel_center = vec_scale((t_vect2d){x - center.x, y - center.y}, (double)1/vars->tile_size);
				t_vect2d coord_transform = mat_mult(mat_rot, coord_rel_center);
				t_vect2d map_coord = vec_add(vars->player.pos, coord_transform);
				int val = get_map_val(vars, floor(map_coord.x), floor(map_coord.y));
				uint32_t color = (val == WALL) * TILE_COL_1
							   + (val == EMPTY) * TILE_COL_2
							   + (val == DOOR) * TILE_COL_3;
				if (val != EMPTY)
					prot_put_pixel(vars->img, x, y, color);
				else if (!((x + y) % 2))
					prot_put_pixel(vars->img, x, y, color);
			}
			else if (inside_circle((t_ivect2d){x, y}, (t_ivect2d){center.x, center.y}, MINI_MAP_WIDTH / 2))
					prot_put_pixel(vars->img, x, y, MINI_MAP_BORDER);
		}
	}
	// draw_star(vars, center, 0x0000FFFF);
	put_mini_map_cursor(vars, (t_ivect2d){center.x, center.y});
	t_vect2d center_to_n = vec_scale(vars->player.dir, (double)MINI_MAP_WIDTH / 2 - 5);
	t_ivect2d north_center = (t_ivect2d){center.x - center_to_n.x, center.y + center_to_n.y};
	int n_radius = 20;
	draw_circle(vars, north_center, n_radius, MINI_MAP_BORDER);
	draw_texture(vars, vars->nletter_tex, (t_ivect2d){north_center.x - n_radius, north_center.y - n_radius});
	// draw_line(vars, center, forward, 0xFF0000FF);
	// draw_line(vars, center, right, 0x0000FFFF);
}
