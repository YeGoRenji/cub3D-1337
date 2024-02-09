/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_unary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:36:49 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/09 17:43:04 by ylyoussf         ###   ########.fr       */
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
