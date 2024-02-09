/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:12:33 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/09 17:43:12 by ylyoussf         ###   ########.fr       */
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

typedef struct s_mat2x2
{
	t_vect2d c1;
	t_vect2d c2;
}			t_mat2x2;

typedef struct s_shape
{
	int		x;
	int		y;
	int		size;
}				t_shape;

/* VECTOR OPERATIONS */
t_vect2d	vec_add(t_vect2d vec1, t_vect2d vec2);
t_vect2d	vec_sub(t_vect2d vec1, t_vect2d vec2);
t_vect2d	vec_scale(t_vect2d vec, double scale);
double		vec_mag(t_vect2d vec);
t_vect2d	vec_norm(t_vect2d vec);
double		vec_dot(t_vect2d vec1, t_vect2d vec2);
t_vect2d	mat_mult(t_mat2x2 mat, t_vect2d v);

/* UTILS */
int		clamp_value(int val, int min, int max);
bool	inside_circle(t_ivect2d pt, t_ivect2d center, int radius);
void	*ifelse(bool condition, void *truthy, void *falsy);

#endif
