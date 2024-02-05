/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:12:33 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/05 04:21:17 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vect2d
{
	double		x;
	double		y;
}				t_vect2d;

typedef struct s_ivect2d
{
	int		x;
	int		y;
}				t_ivect2d;

/* VECTOR OPERATIONS */
t_vect2d	vector_add(t_vect2d *vec1, t_vect2d *vec2);
t_vect2d	vector_sub(t_vect2d *vec1, t_vect2d *vec2);
t_vect2d	vector_scale(t_vect2d *vec, double scale);
double		vector_magnitude(t_vect2d *vec);
t_vect2d	vector_normalize(t_vect2d *vec);
double		vector_dot(t_vect2d *vec1, t_vect2d *vec2);

/* UTILS */
int		clamp_value(int val, int min, int max);
bool	inside_circle(t_ivect2d pt, t_ivect2d center, int radius);

#endif
