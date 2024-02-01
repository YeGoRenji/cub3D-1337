/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:47:12 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/01 16:27:30 by ylyoussf         ###   ########.fr       */
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

e_orientation get_wall_oriantation(t_rayhit *hit, t_vect2d *raydir)
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

t_rayhit ray_cast_dda(t_vars *vars, t_vect2d ray)
{
	t_vect2d	ray_normalized;
	ray_normalized = vector_normalize(&ray);

	t_vect2d	delta_dist;
	delta_dist.x = ray_normalized.x == 0 ? 1e30 : fabs(1 / ray_normalized.x);
	delta_dist.y = ray_normalized.y == 0 ? 1e30 : fabs(1 / ray_normalized.y);

	t_vect2d	step;
	step.x = 1 - 2 * (ray.x < 0);
	step.y = 1 - 2 * (ray.y < 0);

	t_vect2d	side_dist;
	t_vect2d	*pos;

	pos = &vars->player.pos;

	t_ivect2d	mapidx = (t_ivect2d) {
		(int)(vars->player.pos.x),
		(int)(vars->player.pos.y)
	};

	if (ray.x < 0)
		side_dist.x = (pos->x - mapidx.x) * delta_dist.x;
	else
		side_dist.x = (1 - (pos->x - mapidx.x)) * delta_dist.x;
	if (ray.y < 0)
		side_dist.y = (pos->y -  mapidx.y) * delta_dist.y;
	else
		side_dist.y = (1 - (pos->y - mapidx.y)) * delta_dist.y;

	int i = 0;
	int is_x = 0;
	// t_vect2d hit_rel_player;
	t_rayhit hit_data;
	while (i < 1e9)
  	{
		is_x = 0;
		int did_hit = 0;
		if (side_dist.x < side_dist.y)
		{
			is_x = 1;
			side_dist.x += delta_dist.x;
			mapidx.x += step.x;
			hit_data.side = (e_orientation)WE;
		}
		else
		{
			side_dist.y += delta_dist.y;
			mapidx.y += step.y;
			hit_data.side = (e_orientation)NS;
		}

		// Check if ray has hit a wall
		did_hit = get_map_val(vars, mapidx.x, mapidx.y) > 0;

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
		if (did_hit)
			break;
		++i;
	}


	hit_data.where = vector_scale(&ray_normalized, hit_data.dist);
	// t_vect2d visual_hit = vector_scale(&hit_data.where, vars->tile_size);
	hit_data.where = vector_add(&vars->player.pos, &hit_data.where);
	if ((int)hit_data.side == WE)
	{
		hit_data.pos_in_texture =  fabs(hit_data.where.y - mapidx.y);
		if (ray.x < 0)
			hit_data.pos_in_texture = 1 - hit_data.pos_in_texture;
	}
	else
	{
		hit_data.pos_in_texture = fabs(hit_data.where.x - mapidx.x);
		if (ray.y > 0)
			hit_data.pos_in_texture = 1 - hit_data.pos_in_texture;
	}

	// t_vect2d forward_scaled = vector_scale(&vars->player.dir, vars->dist_to_plane);
	// hit_data.dist *=  vector_magnitude(&forward_scaled) / vector_magnitude(&ray);
	hit_data.dist /= vector_magnitude(&ray);
	hit_data.side = get_wall_oriantation(&hit_data, &ray_normalized);

	// draw_star(vars, vector_add(&visual_player_pos, &visual_hit), 0xFF0000FF);
	// draw_line(vars, visual_player_pos, vector_add(&visual_player_pos, &visual_hit), 0xFFFFFFFF);
	return hit_data;
}


void  draw_stripe(t_vars *vars, t_rayhit *hit, int x_stripe, int drawStart, int drawEnd, int fog, int width)
{
	int	half_width = width >> 1;
	double h_percent = hit->pos_in_texture;
	mlx_texture_t *tex = vars->wall_tex[hit->side];
	int start = drawStart;
	if (start < 0) start = 0;
	int end = drawEnd;
	if (end >= vars->mlx->height) end = vars->mlx->height - 1;

	// for (int y = drawStart - 50; y < drawStart; ++y)
	// 	for (int x = x_stripe - half_width; x <= x_stripe + half_width; x++)
	// 		prot_put_pixel(vars->img, x, y, 0x5050FF50);
	
	// Shadow ??
	if (hit->side == SOUTH || hit->side == WEST)
		fog = clamp_value(fog - 0x69, 0, 0xFF);
	for (int y = start; y <= end - 1; ++y)
	{
		double v_percent = (double)(y - drawStart) / (drawEnd - drawStart);
		int x_tex = h_percent * tex->width;
		int y_tex = v_percent * tex->height;
		uint32_t color =  ((uint32_t *)tex->pixels)[y_tex * tex->width + x_tex];
		color = (color & 0xFFFFFF00) | fog;
		for (int x = x_stripe - half_width; x <= x_stripe + half_width; x++)
			prot_put_pixel(vars->img, x, y, color);
	}
}

void draw_wall_stripes(t_vars *vars)
{
	t_vect2d	forward_scaled;
	t_vect2d	side_dir;
	int			i;

	forward_scaled = vars->player.dir;
	side_dir = (t_vect2d){vars->player.dir.y, -vars->player.dir.x};

	int steps = vars->mlx->width / vars->nb_vert_stripes;
	int64_t fog = 0xFF;
	for (i = 0; i < vars->mlx->width; i += steps)
	{
		double cameraX = 2 * (i + ((double)WIDTH/2 - (double)vars->mlx->width/2)) / (double)(WIDTH) - 1;

		t_vect2d var_side = (t_vect2d){-cameraX * vars->fov * side_dir.x, -cameraX * vars->fov * side_dir.y};
		t_vect2d ray = vector_add(&forward_scaled, &var_side);
		t_rayhit hit = ray_cast_dda(vars, ray);
		int h = vars->mlx->height;
		int lineHeight = (int)(HEIGHT / (hit.dist * vars->fov));

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		// if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		// if (drawEnd >= h) drawEnd = h - 1;

		fog = clamp_value(0xFF + 10 - hit.dist * 20, 0, 0xFF);
		// hit.side ? ((0xFF5050 << 8) | fog) : ((0x50FF50 << 8) | fog)
		draw_stripe(vars, &hit, i, drawStart, drawEnd, fog, steps);
	}
}
