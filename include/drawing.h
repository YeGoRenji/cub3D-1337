/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:21:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/27 03:14:57 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include <structs.h>
# include <stdio.h>

void	draw_line(t_vars *vars, t_vect2d pt1, t_vect2d pt2, uint32_t color);
void	prot_put_pixel(mlx_image_t *image, int x, int y, uint32_t color);
bool	inside_circle(t_ivect2d pt, t_ivect2d center, int radius);
void	clear_screen(t_vars* vars, uint32_t color);

/* Primitives */
void	draw_square(t_vars* vars, t_vect2d anchor, int width, uint32_t color);
void	draw_star(t_vars *vars, t_vect2d center, uint32_t color);
void	draw_trig(t_vars *vars, t_vect2d pos, int width, int height, uint32_t color);
void	draw_circle(t_vars *vars, t_ivect2d center, int radius, uint32_t color);
void	draw_texture(t_vars *vars, mlx_texture_t *texture, t_ivect2d pos);


/* Walls */
void	draw_wall_stripes(t_vars *vars);
int		get_map_val(t_vars *vars, int x, int y);

/* Mini map */
void mini_map(t_vars *vars, t_ivect2d pos);

#endif
