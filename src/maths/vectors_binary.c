/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:11:38 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/09 17:42:44 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.h>

t_vect2d	vec_add(t_vect2d vec1, t_vect2d vec2)
{
	return ((t_vect2d){vec1.x + vec2.x, vec1.y + vec2.y});
}

t_vect2d	vec_sub(t_vect2d vec1, t_vect2d vec2)
{
	return ((t_vect2d){vec1.x - vec2.x, vec1.y - vec2.y});
}

t_vect2d	vec_scale(t_vect2d vec, double scale)
{
	return ((t_vect2d){scale * vec.x, scale * vec.y});
}

double	vec_dot(t_vect2d vec1, t_vect2d vec2)
{
	return (vec1.x * vec2.x + vec1.x * vec2.y);
}

t_vect2d	mat_mult(t_mat2x2 mat, t_vect2d v)
{
	t_vect2d	vec;
	t_vect2d	s1;
	t_vect2d	s2;

	s1 = vec_scale(mat.c1, v.x);
	s2 = vec_scale(mat.c2, v.y);
	vec = (t_vect2d){0, 0};
	vec = vec_add(vec, s1);
	vec = vec_add(vec, s2);
	return (vec);
}
