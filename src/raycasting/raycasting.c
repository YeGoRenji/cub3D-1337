/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:16:57 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/10 16:18:27 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raycasting.h>

int	get_map_val(t_vars *vars, int x, int y)
{
	if (x < 0 || x >= vars->map.width)
		return (0);
	if (y < 0 || y >= vars->map.height)
		return (0);
	return (vars->map.data[y * vars->map.width + x]);
}

t_orientation	get_wall_oriantation(t_rayhit *hit, t_vect2d *raydir)
{
	if ((int)hit->side == NS)
	{
		if (raydir->y > 0)
			return (NORTH);
		return (SOUTH);
	}
	if (raydir->x > 0)
		return (WEST);
	return (EAST);
}

t_rayhit	ray_cast_dda(t_vars *vars, t_vect2d from, t_vect2d ray)
{
	t_rayhit	hit_data;
	t_vect2d	ray_normalized;
	ray_normalized = vec_norm(ray);

	t_vect2d	delta_dist;
	delta_dist.x = ifelsed(ray_normalized.x == 0, 1e30, fabs(1 / ray_normalized.x));
	delta_dist.y = ifelsed(ray_normalized.y == 0, 1e30, fabs(1 / ray_normalized.y));

	t_vect2d	step;
	step.x = 1 - 2 * (ray.x < 0);
	step.y = 1 - 2 * (ray.y < 0);

	t_vect2d	side_dist;
	t_vect2d	*pos;

	pos = &from;

	hit_data.map = (t_ivect2d) {
		(int)floor(vars->player.pos.x),
		(int)floor(vars->player.pos.y)
	};

	if (ray.x < 0)
		side_dist.x = (pos->x - hit_data.map.x) * delta_dist.x;
	else
		side_dist.x = (1 - (pos->x - hit_data.map.x)) * delta_dist.x;
	if (ray.y < 0)
		side_dist.y = (pos->y -  hit_data.map.y) * delta_dist.y;
	else
		side_dist.y = (1 - (pos->y - hit_data.map.y)) * delta_dist.y;

	int i = 0;
	int is_x = 0;
	// t_vect2d hit_rel_player;
	
	hit_data.hit_what = 0;
	while (i < 1e3)
  	{
		is_x = 0;
		if (side_dist.x < side_dist.y)
		{
			is_x = 1;
			side_dist.x += delta_dist.x;
			hit_data.map.x += step.x;
			hit_data.side = (t_orientation)WE;
		}
		else
		{
			side_dist.y += delta_dist.y;
			hit_data.map.y += step.y;
			hit_data.side = (t_orientation)NS;
		}

		hit_data.hit_what = get_map_val(vars, hit_data.map.x, hit_data.map.y);

		if (is_x)
		{
			hit_data.dist = side_dist.x - delta_dist.x;
			// hit_rel_player = vector_scale(&ray_normalized, side_dist.x - delta_dist.x);
			// t_vect2d visual_next_side_x = vector_scale(&ray_normalized, side_dist.x - delta_dist.x);
			// visual_next_side_x = vector_scale(&visual_next_side_x, vars->tile_size);
			// draw_star(vars, vector_add(&visual_player_pos, &visual_next_side_x), hit ? 0xFF0000FF : 0xFFFF00FF);
		}
		else
		{
			hit_data.dist = side_dist.y - delta_dist.y;
			// hit_rel_player = vector_scale(&ray_normalized, side_dist.y - delta_dist.y);
			// t_vect2d visual_next_side_y = vector_scale(&ray_normalized, side_dist.y - delta_dist.y);
			// visual_next_side_y = vector_scale(&visual_next_side_y, vars->tile_size);
			// draw_star(vars, vector_add(&visual_player_pos, &visual_next_side_y), hit ? 0xFF0000FF : 0x00FFFFFF);
		}
		// TODO : refactor repetitive code ?
		if (hit_data.hit_what == DOOR)
		{
			// hit_data.dist += 0.5;
			hit_data.where = vec_scale(ray_normalized, hit_data.dist);
			hit_data.where = vec_add(vars->player.pos, hit_data.where);
			if ((int)hit_data.side == WE)
				hit_data.pos_in_texture = hit_data.where.y - hit_data.map.y;
			else
				hit_data.pos_in_texture = hit_data.where.x - hit_data.map.x;
			// double dist_to_door = hit_data.dist;
			t_vect2d center_door = (t_vect2d){hit_data.map.x + 0.5, hit_data.map.y + 0.5};
			t_vect2d diff = vec_sub(*pos, center_door);
			double dist_to_door = vec_mag(diff);
			if (1 - hit_data.pos_in_texture < dist_to_door - 1)
			{
				// double old_val = hit_data.pos_in_texture;
				hit_data.pos_in_texture += (dist_to_door < 2) * dist_to_door;
				hit_data.pos_in_texture = fabs(hit_data.pos_in_texture - floor(hit_data.pos_in_texture));
				// if (0 <= old_val && old_val <= 1)
					break;
			}
		}
		else if (hit_data.hit_what > 0)
			break;
		++i;
	}

	// TODO : refactor repetitive code ?
	if (hit_data.hit_what != DOOR)
	{
		hit_data.where = vec_scale(ray_normalized, hit_data.dist);
		// t_vect2d visual_hit = vector_scale(&hit_data.where, vars->tile_size);
		hit_data.where = vec_add(vars->player.pos, hit_data.where);
		// t_vect2d epsilon = vector_scale(&step, 0.5);
		if ((int)hit_data.side == WE)
		{
			hit_data.pos_in_texture =  fabs(hit_data.where.y - hit_data.map.y);
			if (ray.x < 0)
				hit_data.pos_in_texture = 1 - hit_data.pos_in_texture;
		}
		else
		{
			hit_data.pos_in_texture = fabs(hit_data.where.x - hit_data.map.x);
			if (ray.y > 0)
				hit_data.pos_in_texture = 1 - hit_data.pos_in_texture;
		}
	}
	// t_vect2d forward_scaled = vector_scale(&vars->player.dir, vars->dist_to_plane);
	// hit_data.dist *=  vector_magnitude(&forward_scaled) / vector_magnitude(&ray);
	// if (hit_data.hit_what == DOOR)
	// 	hit_data.dist += 0.5;
	hit_data.dist /= vec_mag(ray);
	hit_data.side = get_wall_oriantation(&hit_data, &ray_normalized);

	// draw_star(vars, vector_add(&visual_player_pos, &visual_hit), 0xFF0000FF);
	// draw_line(vars, visual_player_pos, vector_add(&visual_player_pos, &visual_hit), 0xFFFFFFFF);
	return hit_data;
}
