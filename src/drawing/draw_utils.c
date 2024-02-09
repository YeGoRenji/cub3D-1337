/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:01:52 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/09 01:51:20 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	clear_screen(t_vars *vars, uint32_t color)
{
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (y < vars->img->height)
	{
		x = 0;
		while (x < vars->img->width)
		{
			prot_put_pixel(vars->img, x, y, color);
			++x;
		}
		++y;
	}
}
