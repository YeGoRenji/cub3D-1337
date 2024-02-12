/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:16:16 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/11 19:18:24 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

static void	draw_digit(t_vars *vars, int digit, t_shape square, uint32_t color)
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
				draw_square(vars, (t_vect2d){square.x + iter.x * square.size,
					square.y + iter.y * square.size}, square.size, color);
			++iter.x;
		}
		iter = (t_ivect2d){0, iter.y + 1};
	}
}

static void	draw_number(t_vars *vars, int number, t_shape sq, uint32_t color)
{
	int	i;

	draw_digit(vars, number % 10, (t_shape){sq.x - 3 * sq.size - sq.size, sq.y
		+ 2, sq.size}, 0x000000FF);
	draw_digit(vars, number % 10, (t_shape){sq.x - 3 * sq.size - sq.size, sq.y,
		sq.size}, color);
	number /= 10;
	i = 2;
	while (number > 0)
	{
		draw_digit(vars, number % 10, (t_shape){sq.x - (3 * sq.size + sq.size
				/ 2) * i - sq.size, sq.y + 2, sq.size}, 0x000000FF);
		draw_digit(vars, number % 10, (t_shape){sq.x - (3 * sq.size + sq.size
				/ 2) * i - sq.size, sq.y, sq.size}, color);
		number /= 10;
		++i;
	}
}

void	draw_fps(t_vars *vars)
{
	static double	old_time;
	static int		fps;
	double			current_time;

	current_time = mlx_get_time();
	if (current_time - old_time > 0.2)
	{
		fps = 1 / vars->mlx->delta_time;
		old_time = current_time;
	}
	draw_number(vars, fps, (t_shape){vars->mlx->width, 10, 10}, FPS_COLOR);
}

void	*fps_thread(void *param)
{
	t_vars	*vars;

	vars = param;
	while (1)
		draw_fps(vars);
	return (NULL);
}
