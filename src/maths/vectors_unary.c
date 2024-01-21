/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_unary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:36:49 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/21 17:37:41 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.h>

double	vector_magnitude(t_vect2d *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y));
}

t_vect2d	vector_normalize(t_vect2d *vec)
{
	double	mag;

	mag = vector_magnitude(vec);
	return ((t_vect2d){
		vec->x / mag,
		vec->y / mag
	});
}
