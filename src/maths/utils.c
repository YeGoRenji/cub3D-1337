/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:17:53 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/05 04:11:53 by ylyoussf         ###   ########.fr       */
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

int	big_to_little(int big)
{
	int	little;

	little = 0;
	little |= (big & 0x000000FF) << 24;
	little |= (big & 0xFF000000) >> 24;
	little |= (big & 0x00FF0000) >> 8;
	little |= (big & 0x0000FF00) << 8;
	return (little);
}
