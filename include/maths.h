/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:12:33 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/22 20:33:02 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>

typedef struct s_vect2d
{
	double		x;
	double		y;
}				t_vect2d;

/* VECTOR OPERATIONS */
t_vect2d	vector_add(t_vect2d *vec1, t_vect2d *vec2);
t_vect2d	vector_sub(t_vect2d *vec1, t_vect2d *vec2);
t_vect2d	vector_scale(t_vect2d *vec, double scale);
double		vector_magnitude(t_vect2d *vec);
t_vect2d	vector_normalize(t_vect2d *vec);
double		vector_dot(t_vect2d *vec1, t_vect2d *vec2);

/* UTILS */
double		abs_f(double a);

#endif
