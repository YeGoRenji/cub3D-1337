/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:17:23 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/14 21:17:34 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <structs.h>
# include <parse.h>

t_rayhit		ray_cast_dda(t_vars *vars, t_vect2d ray);
int				get_map_val(t_vars *vars, int x, int y);
void			update_hit_data(t_vars *vars, t_rayhit *hit_data,
					t_vect2d ray_normalized, bool orientation_spec);
t_orientation	get_wall_oriantation(t_rayhit *hit, const t_vect2d *raydir);
bool			handle_door(t_vars *vars, t_rayhit *hit_data,
					t_vect2d ray_normalized);

#endif
