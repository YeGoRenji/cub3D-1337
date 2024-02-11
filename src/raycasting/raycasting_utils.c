/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:18:49 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/11 17:19:29 by ylyoussf         ###   ########.fr       */
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

t_orientation	get_wall_oriantation(t_rayhit *hit, const t_vect2d *raydir)
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

void	update_hit_data(t_vars *vars, t_rayhit *hit_data,
		t_vect2d ray_normalized, bool orientation_spec)
{
	hit_data->where = vec_scale(ray_normalized, hit_data->dist);
	hit_data->where = vec_add(vars->player.pos, hit_data->where);
	if ((int)hit_data->side == WE)
	{
		hit_data->pos_in_texture = hit_data->where.y - hit_data->map.y;
		if (orientation_spec && ray_normalized.x < 0)
			hit_data->pos_in_texture = 1 - fabs(hit_data->pos_in_texture);
	}
	else
	{
		hit_data->pos_in_texture = hit_data->where.x - hit_data->map.x;
		if (orientation_spec && ray_normalized.y > 0)
			hit_data->pos_in_texture = 1 - fabs(hit_data->pos_in_texture);
	}
}

bool	handle_door(t_vars *vars, t_rayhit *hit_data, t_vect2d ray_normalized)
{
	t_vect2d	center_door;
	double		dist_to_door;

	update_hit_data(vars, hit_data, ray_normalized, false);
	center_door = (t_vect2d){hit_data->map.x + 0.5, hit_data->map.y + 0.5};
	dist_to_door = vec_mag(vec_sub(vars->player.pos, center_door));
	if (1 - hit_data->pos_in_texture < dist_to_door - 1)
	{
		hit_data->pos_in_texture += (dist_to_door < 2) * dist_to_door;
		hit_data->pos_in_texture = fabs(hit_data->pos_in_texture
				- floor(hit_data->pos_in_texture));
		return (true);
	}
	return (false);
}
