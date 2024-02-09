/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:50:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/09 20:52:50 by ylyoussf         ###   ########.fr       */
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

void	draw_north(t_vars *vars, t_ivect2d center)
{
	const int	circle_radius = 20;
	t_vect2d	center_to_n;
	t_ivect2d	north_center;

	center_to_n = vec_scale(vars->player.dir, (double)MINI_MAP_WIDTH / 2 - 5);
	north_center = (t_ivect2d){
		center.x - center_to_n.x,
		center.y + center_to_n.y
	};
	draw_circle(vars, north_center, circle_radius, MINI_MAP_BORDER);
	draw_texture(vars, vars->nletter_tex, (t_ivect2d){
		north_center.x - circle_radius,
		north_center.y - circle_radius
	});
}

void	mini_map(t_vars *vars, t_ivect2d pos)
{
	// TODO: the signs of the vectors are just tweaked bruteforce (UNDERSTAND MORE ?)
	t_ivect2d	it;
	t_vect2d forward = (t_vect2d){vars->player.dir.x, -vars->player.dir.y};
	t_vect2d right = (t_vect2d){-vars->player.dir.y, -vars->player.dir.x};
	t_ivect2d center = (t_ivect2d){MINI_MAP_WIDTH / 2 + pos.x, MINI_MAP_WIDTH / 2 + pos.y};

	// Testing
	t_mat2x2 mat_rot = {
		{forward.y, -right.y},
		{-forward.x, right.x}
	};
	it = pos;
	while (it.y < pos.y + MINI_MAP_WIDTH)
	{
		while (it.x < pos.x + MINI_MAP_WIDTH)
		{
			if (inside_circle(it, center, MINI_MAP_WIDTH / 2 - 10))
			{
				t_vect2d rel_center = vec_scale(vec_sub(itovec(it), itovec(center)), (double)1/vars->tile_size);
				t_vect2d transformed = mat_mult(mat_rot, rel_center);
				t_vect2d map_coord = vec_add(vars->player.pos, transformed);
				int val = get_map_val(vars, floor(map_coord.x), floor(map_coord.y));
				uint32_t color = (val == WALL) * TILE_COL_WALL
							   + (val == EMPTY) * TILE_COL_EMPTY
							   + (val == DOOR) * TILE_COL_DOOR;
				if (val != EMPTY || !((it.x + it.y) % 2))
					prot_put_pixel(vars->img, it.x, it.y, color);
			}
			else if (inside_circle(it, center, MINI_MAP_WIDTH / 2))
					prot_put_pixel(vars->img, it.x, it.y, MINI_MAP_BORDER);
			++it.x;
		}
		it = (t_ivect2d){pos.x, it.y + 1};
	}
	put_mini_map_cursor(vars, center);
	draw_north(vars, center);
}
