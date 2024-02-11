/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_unary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:36:49 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/11 15:28:50 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.h>

double	vec_mag(t_vect2d vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

t_vect2d	vec_norm(t_vect2d vec)
{
	double	mag;

	mag = vec_mag(vec);
	return ((t_vect2d){
		vec.x / mag,
		vec.y / mag
	});
}

t_vect2d	itovec(t_ivect2d ivec)
{
	return ((t_vect2d){ivec.x, ivec.y});
}

t_ivect2d	vectoi(t_vect2d vec)
{
	return ((t_ivect2d){vec.x, vec.y});
}
