/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:16:16 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/04 20:51:13 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <drawing.h>

static void draw_digit(t_vars *vars, int digit, int x, int y, int size)
{
	int i = 0;
	int j = 0;
	int digits_patt[5][3 * 10] =  {
		{1, 1, 1,  0, 0, 1,  1, 1, 1,  1, 1, 1,  1, 0, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1},
		{1, 0, 1,  0, 0, 1,  0, 0, 1,  0, 0, 1,  1, 0, 1,  1, 0, 0,  1, 0, 0,  0, 0, 1,  1, 0, 1,  1, 0, 1},
		{1, 0, 1,  0, 0, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  0, 0, 1,  1, 1, 1,  1, 1, 1},
		{1, 0, 1,  0, 0, 1,  1, 0, 0,  0, 0, 1,  0, 0, 1,  0, 0, 1,  1, 0, 1,  0, 0, 1,  1, 0, 1,  0, 0, 1},
		{1, 1, 1,  0, 0, 1,  1, 1, 1,  1, 1, 1,  0, 0, 1,  1, 1, 1,  1, 1, 1,  0, 0, 1,  1, 1, 1,  1, 1, 1},
	};

	digit = digit % 10;
	while (i < 5)
	{
		j = 0;
		while (j < 3)
		{
			if (digits_patt[i][j + digit * 3])
				draw_square(vars, (t_vect2d){x + j * size, y + i * size}, size, 0xFFFFFFFF);
			++j;
		}
		++i;
	}
}

void draw_fps(t_vars *vars)
{
	static double	old_time = 0;
	double			current_time;
	int				fps;

	fps = (int)(1 / vars->mlx->delta_time);
	current_time = mlx_get_time();
	int tmp_size = 10;
	draw_digit(vars, fps, vars->mlx->width - 3 * tmp_size - 10, 10, tmp_size);
	draw_digit(vars, fps / 10, vars->mlx->width - 6 * tmp_size - 20, 10, tmp_size);
	if (current_time - old_time > 0.1)
	{
		printf("fps: %d        nvs: %d        fov: %d        \r" , fps, vars->nb_vert_stripes, vars->fov);
		fflush(stdout);
		old_time = current_time;
	}
}
