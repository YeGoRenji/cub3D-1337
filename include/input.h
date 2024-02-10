/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 03:20:37 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/10 03:26:41 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <structs.h>

void	get_input_mvt(t_vars *vars, t_vect2d *input_mvt);
void	view_control(t_vars	*vars);
void	limit_values(t_vars *vars);

#endif
