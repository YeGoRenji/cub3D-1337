/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:21:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/18 20:52:03 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include <structs.h>

void	draw_line(t_vars *vars, t_vect2d pt1, t_vect2d pt2, uint32_t color);
void	prot_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color);

#endif
