/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:24:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/11 15:24:09 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void	split_draw(t_vars *vars, void *(*func)(void *), t_ivect2d size,
		t_ivect2d pos)
{
	int				rg_width;
	int				rg_height;
	t_thread_artist	art[THREADS];
	pthread_t		threads[THREADS];
	int				i;

	rg_width = size.x / THREADS;
	rg_height = size.y;
	i = 0;
	while (i < THREADS)
	{
		art[i].vars = vars;
		art[i].start = (t_ivect2d){pos.x + i * rg_width, pos.y};
		art[i].end = (t_ivect2d){pos.x + (i + 1) * rg_width, pos.y + rg_height};
		pthread_create(threads + i, NULL, func, art + i);
		++i;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(threads[i++], NULL);
}
