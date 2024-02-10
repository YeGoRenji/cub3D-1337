/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:17:53 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/10 04:09:22 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.h>

int	clamp_value(int val, int min, int max)
{
	val += (val < min) * (min - val);
	val += (val > max) * (max - val);
	return (val);
}

bool	inside_circle(t_ivect2d pt, t_ivect2d center, int radius)
{
	t_ivect2d	diff;

	diff = (t_ivect2d){pt.x - center.x, pt.y - center.y};
	if (diff.x * diff.x + diff.y * diff.y <= radius * radius)
		return (true);
	return (false);
}

void	*ifelse(bool condition, void *truthy, void *falsy)
{
	if (condition)
		return (truthy);
	return (falsy);
}

double	ifelsed(bool condition, double truthy, double falsy)
{
	if (condition)
		return (truthy);
	return (falsy);
}

t_vect2d	itovec(t_ivect2d ivec)
{
	return ((t_vect2d){ivec.x, ivec.y});
}

t_ivect2d	vectoi(t_vect2d vec)
{
	return ((t_ivect2d){vec.x, vec.y});
}
