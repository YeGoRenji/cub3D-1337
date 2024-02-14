/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:16:57 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/14 12:49:38 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raycasting.h>

void	go_next_square(t_vect2d *side_dist, t_vect2d delta_dist,
		t_vect2d step, t_rayhit *hit_data)
{
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist.x;
		hit_data->map.x += step.x;
		hit_data->side = (t_orientation)WE;
		hit_data->dist = side_dist->x - delta_dist.x;
	}
	else
	{
		side_dist->y += delta_dist.y;
		hit_data->map.y += step.y;
		hit_data->side = (t_orientation)NS;
		hit_data->dist = side_dist->y - delta_dist.y;
	}
}

void	iterate_dda(t_vars *vars, t_rayhit *hit_dt, t_vect2d ray_norm)
{
	t_vect2d	delta_dist;
	t_vect2d	step;
	t_vect2d	side_dist;
	int			i;

	delta_dist.x = ifelsed(ray_norm.x == 0, 1e30, fabs(1 / ray_norm.x));
	delta_dist.y = ifelsed(ray_norm.y == 0, 1e30, fabs(1 / ray_norm.y));
	step.x = 1 - 2 * (ray_norm.x < 0);
	step.y = 1 - 2 * (ray_norm.y < 0);
	side_dist.x = (vars->player.pos.x - hit_dt->map.x) * delta_dist.x;
	side_dist.x += (ray_norm.x >= 0) * (delta_dist.x - 2 * side_dist.x);
	side_dist.y = (vars->player.pos.y - hit_dt->map.y) * delta_dist.y;
	side_dist.y += (ray_norm.y >= 0) * (delta_dist.y - 2 * side_dist.y);
	i = 0;
	hit_dt->hit_what = 0;
	while (i < 1e3)
	{
		go_next_square(&side_dist, delta_dist, step, hit_dt);
		hit_dt->hit_what = get_map_val(vars, hit_dt->map.x, hit_dt->map.y);
		if ((hit_dt->hit_what > 0) && 
			(hit_dt->hit_what == WALL || handle_door(vars, hit_dt, ray_norm)))
				break ;
		++i;
	}
	hit_dt->dist = ifelsed(i >= 1e3, 2000, hit_dt->dist);
}

t_rayhit	ray_cast_dda(t_vars *vars, t_vect2d ray)
{
	t_rayhit		hit_data;
	const t_vect2d	ray_normalized = vec_norm(ray);

	hit_data.map = (t_ivect2d){(int)floor(vars->player.pos.x),
		(int)floor(vars->player.pos.y)};
	iterate_dda(vars, &hit_data, ray_normalized);
	if (hit_data.hit_what != DOOR)
		update_hit_data(vars, &hit_data, ray_normalized, true);
	hit_data.dist /= vec_mag(ray);
	hit_data.side = get_wall_oriantation(&hit_data, &ray_normalized);
	return (hit_data);
}
