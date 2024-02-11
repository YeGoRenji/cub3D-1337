/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 03:20:37 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/11 18:13:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <stdlib.h>
# include <structs.h>

/* Player input */
void	get_input_mvt(t_vars *vars, t_vect2d *input_mvt);
void	view_control(t_vars *vars);
void	limit_values(t_vars *vars);

/* Event hooks */
void	on_loop(void *v_vars);
void	on_resize(int32_t new_width, int32_t new_height, void *param);
void	on_click(mlx_key_data_t key_data, void *param);
void	on_mouse(mouse_key_t button, action_t action, modifier_key_t mods,
			void *param);

/* Err */
void	exit_failure(t_vars *vars);

#endif
