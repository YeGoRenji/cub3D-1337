/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:16:16 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/05 03:35:53 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

static void	draw_digit(t_vars *vars, int digit, t_ivect2d pos, int size)
{
	t_ivect2d	iter;
	static int	digits_patt[5][3 * 10] = {
	{1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1,
		0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
	{1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1}};

	iter = (t_ivect2d){0, 0};
	while (iter.y < 5)
	{
		while (iter.x < 3)
		{
			if (digits_patt[iter.y][iter.x + (digit % 10) * 3])
				draw_square(vars, (t_vect2d){pos.x + iter.x * size,
					pos.y + iter.y * size}, size, 0xFF6942FF);
			++iter.x;
		}
		iter = (t_ivect2d){0, iter.y + 1};
	}
}

static void	draw_number(t_vars *vars, int number, t_ivect2d pos, int size)
{
	int	i;

	draw_digit(vars, number % 10,
		(t_ivect2d){pos.x - 3 * size - size, pos.y}, size);
	number /= 10;
	i = 2;
	while (number > 0)
	{
		draw_digit(vars, number % 10,
			(t_ivect2d){pos.x - (3 * size + size / 2) * i - size, pos.y}, size);
		number /= 10;
		++i;
	}
}

void	draw_fps(t_vars *vars)
{
	static double	old_time = 0;
	static int		fps;
	double			current_time;

	current_time = mlx_get_time();
	if (current_time - old_time > 0.2)
	{
		fps = 1 / vars->mlx->delta_time;
		printf("fps: %d        nvs: %d        fov: %d        \r",
			fps, vars->nb_vert_stripes, vars->fov);
		fflush(stdout);
		old_time = current_time;
	}
	draw_number(vars, fps, (t_ivect2d){vars->mlx->width, 10}, 10);
}
