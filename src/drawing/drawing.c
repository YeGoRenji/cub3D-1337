/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:14:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/12 20:29:24 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	ft_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

float	err(t_vect2d *to_draw, t_vect2d *pt1, t_vect2d *pt2)
{
	float	actual_y;
	float	our_y;

	actual_y = pt2->y * (to_draw->x - pt1->x) - pt1->y * (to_draw->x - pt2->x);
	our_y = to_draw->y * (pt2->x - pt1->x);
	return (actual_y - our_y);
}

int64_t	ft_abs(int64_t x)
{
	if (x >= 0)
		return (x);
	return (-x);
}

void	get_direction(t_vect2d *pt1, t_vect2d *pt2, t_dir *dir)
{
	dir->x = 1;
	dir->y = 1;
	if (pt2->y < pt1->y)
		dir->y = -1;
	if (pt2->x < pt1->x)
		dir->x = -1;
}

int	handle_y_x(t_vect2d *pt1, t_vect2d *pt2)
{
	int	y_x_flip;

	y_x_flip = 0;
	if (ft_abs(pt2->y - pt1->y) > ft_abs(pt2->x - pt1->x))
	{
		y_x_flip = 1;
		ft_swap(&pt1->x, &pt1->y);
		ft_swap(&pt2->x, &pt2->y);
	}
	return (y_x_flip);
}

void	my_mlx_point_put(mlx_image_t *img, t_vect2d *pt, int flip, uint32_t color)
{
	int64_t		x;
	int64_t		y;

	x = pt->x;
	y = pt->y;
	if (flip)
	{
		x = pt->y;
		y = pt->x;
	}
	if (!(0 <= x && x < img->width))
		return ;
	if (!(0 <= y && y < img->height))
		return ;

	mlx_put_pixel(img, x , y, color);
}

void	draw_line(t_vars *vars, t_vect2d pt1, t_vect2d pt2, uint32_t color)
{
	t_dir		dir;
	t_vect2d		to_draw;

	dir.is_flipped = handle_y_x(&pt1, &pt2);
	get_direction(&pt1, &pt2, &dir);
	to_draw = pt1;
	while (to_draw.x * dir.x <= pt2.x * dir.x)
	{
		if (ft_abs(err(&to_draw, &pt1, &pt2)) >= 0.5 * ft_abs(pt2.x - pt1.x))
			to_draw.y += dir.y;
		my_mlx_point_put(vars->img, &to_draw, dir.is_flipped, color);
		to_draw.x += dir.x;
	}
}
