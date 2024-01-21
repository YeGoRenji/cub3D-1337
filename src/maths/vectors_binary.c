/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:11:38 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/21 17:45:50 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.h>

t_vect2d	vector_add(t_vect2d *vec1, t_vect2d *vec2)
{
	return ((t_vect2d){
		vec1->x + vec2->x,
		vec1->y + vec2->y
	});
}

t_vect2d	vector_sub(t_vect2d *vec1, t_vect2d *vec2)
{
	return ((t_vect2d){
		vec1->x - vec2->x,
		vec1->y - vec2->y
	});
}

t_vect2d	vector_scale(t_vect2d *vec, double scale)
{
	return ((t_vect2d){
		scale * vec->x,
		scale * vec->y
	});
}

double	vector_dot(t_vect2d *vec1, t_vect2d *vec2)
{
	return (vec1->x * vec2->x + vec1->x * vec2->y);
}
