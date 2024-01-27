/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:47:12 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/27 03:20:59 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

int get_map_val(t_vars *vars, int x, int y)
{
	if (x < 0 || x >= vars->map.width)
		return 1;
	if (y < 0 || y >= vars->map.height)
		return 1;
	return vars->map.data[y * vars->map.width + x];
}

t_rayhit ray_cast_dda(t_vars *vars, t_vect2d ray)
{
	t_vect2d	ray_normalized;
	ray_normalized = vector_normalize(&ray);

	t_vect2d delta_dist;
	delta_dist.x = ray_normalized.x == 0 ? 1e30 : fabs(1 / ray_normalized.x);
	delta_dist.y = ray_normalized.y == 0 ? 1e30 : fabs(1 / ray_normalized.y);

	t_vect2d step;
	step.x = 1 - 2 * (ray.x < 0);
	step.y = 1 - 2 * (ray.y < 0);

	t_vect2d side_dist;
	double pos_x = vars->player.pos.x;// / vars->tile_size;
	double pos_y = vars->player.pos.y;// / vars->tile_size;

	t_ivect2d mapidx = (t_ivect2d) {
		(int)(vars->player.pos.x),
		(int)(vars->player.pos.y)
	};


	if (ray.x < 0)
		side_dist.x = (pos_x - mapidx.x) * delta_dist.x;
	else
		side_dist.x = (1 - (pos_x - mapidx.x)) * delta_dist.x;
	if (ray.y < 0)
		side_dist.y = (pos_y -  mapidx.y) * delta_dist.y;
	else
		side_dist.y = (1 - (pos_y - mapidx.y)) * delta_dist.y;

	// t_vect2d first_side_x = vector_scale(&ray_normalized, side_dist.x);
	// first_side_x = vector_scale(&first_side_x, vars->tile_size);
	// draw_star(vars, vector_add(&visual_player_pos, &first_side_x), 0xFFFF00FF);

	// t_vect2d first_side_y = vector_scale(&ray_normalized, side_dist.y);
	// first_side_y = vector_scale(&first_side_y, vars->tile_size);
	// draw_star(vars, vector_add(&visual_player_pos, &first_side_y), 0x00FFFFFF);

	int i = 0;
	int is_x = 0;
	// t_vect2d hit_rel_player;
	int side = 0;
	t_rayhit hit_data;
	while (i < 1e9)
  	{
		is_x = 0;
		int hit = 0;
		if (side_dist.x < side_dist.y)
		{
			is_x = 1;
			side_dist.x += delta_dist.x;
			mapidx.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			mapidx.y += step.y;
			side = 1;
		}

		// Check if ray has hit a wall
		hit = get_map_val(vars, mapidx.x, mapidx.y) > 0;

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
		if (hit)
			break;
		++i;
	}


	hit_data.where = vector_scale(&ray_normalized, hit_data.dist);
	// t_vect2d visual_hit = vector_scale(&hit_data.where, vars->tile_size);
	hit_data.where = vector_add(&vars->player.pos, &hit_data.where);
	hit_data.side = side;

	// t_vect2d forward_scaled = vector_scale(&vars->player.dir, vars->dist_to_plane);
	// hit_data.dist *=  vector_magnitude(&forward_scaled) / vector_magnitude(&ray);
	hit_data.dist /= vector_magnitude(&ray);

	// draw_star(vars, vector_add(&visual_player_pos, &visual_hit), 0xFF0000FF);
	// draw_line(vars, visual_player_pos, vector_add(&visual_player_pos, &visual_hit), 0xFFFFFFFF);
	return hit_data;
}

void  draw_stripe(t_vars *vars, int x_stripe, int drawStart, int drawEnd, uint32_t color, int width)
{
	int	half_width = width >> 1;

	// for (int y = drawStart - 50; y < drawStart; ++y)
	// 	for (int x = x_stripe - half_width; x <= x_stripe + half_width; x++)
	// 		prot_put_pixel(vars->img, x, y, 0x5050FF50);
	for (int y = drawStart; y <= drawEnd; ++y)
		for (int x = x_stripe - half_width; x <= x_stripe + half_width; x++)
			prot_put_pixel(vars->img, x, y, color);
}

// t_rayhit ray_cast_dda(t_vars *vars, t_vect2d ray);

void draw_wall_stripes(t_vars *vars)
{
	t_vect2d	forward_scaled;
	t_vect2d	side_dir;
	int			i;

	forward_scaled = vars->player.dir;
	side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};

	int steps = WIDTH / vars->nb_vert_stripes;
	int64_t fog = 0xFF;
	for (i = 0; i < WIDTH; i += steps)
	{
		double cameraX = 2 * i / (double)(WIDTH) - 1;

		t_vect2d var_side = (t_vect2d){-cameraX * vars->fov * side_dir.x, -cameraX * vars->fov * side_dir.y};
		t_vect2d ray = vector_add(&forward_scaled, &var_side);
		t_rayhit hit = ray_cast_dda(vars, ray);
		int h = HEIGHT;
		int lineHeight = (int)(h / (hit.dist * vars->fov));

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h) drawEnd = h - 1;

		fog = 0xFF - hit.dist * 20;
		fog = clamp_value(fog, 0, 0xFF);
		draw_stripe(vars, i, drawStart, drawEnd, hit.side ? ((0xFF5050 << 8) | fog) : ((0x50FF50 << 8) | fog), steps);
	}
}
