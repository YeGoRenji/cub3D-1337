/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 03:20:37 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/14 11:33:08 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <stdlib.h>
# include <drawing.h>
# include <structs.h>

/* Player input */
void	get_input_mvt(t_vars *vars, t_vect2d *input_mvt);
void	view_control(t_vars *vars);
void	limit_values(t_vars *vars);

/* Event hooks */
void	install_hooks(t_vars *vars);

/* Err */
void	exit_failure(t_vars *vars);
void	err_and_exit(char *err);
void	load_img_err(const char *path);

/* init */
void	initialize(t_vars *vars);

#endif
