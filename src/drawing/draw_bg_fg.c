/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 04:23:22 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/08 03:46:46 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <drawing.h>

void *draw_skybox(void *param)
{
	t_thread_artist	*art = param;
	t_ivect2d		iter;
	mlx_texture_t	*tex = art->vars->sky_tex;
	uint32_t		color;
	int				offset;

	iter = art->start;
	offset = tex->width * (art->vars->look_angle / (2 * M_PI));
	while (iter.y < art->end.y)
	{
		while (iter.x < art->end.x)
		{
			int y_tex = (tex->height) * iter.y / art->vars->mlx->height;
			int x_tex = (tex->width) * iter.x / art->vars->mlx->width;
			x_tex = (x_tex + offset) % tex->width;
			color = ((uint32_t *)tex->pixels)[y_tex * tex->width + x_tex];
			prot_put_pixel(art->vars->img, iter.x, iter.y, color);
			++iter.x;
		}
		iter = (t_ivect2d){art->start.x, iter.y + 1};
	}
	return (NULL);
}

void *draw_floor(void *param)
{
	t_thread_artist	*art = param;
	t_ivect2d		iter;

	iter = art->start;
	while (iter.y < art->end.y)
	{
		while (iter.x < art->end.x)
		{
			prot_put_pixel(art->vars->img, iter.x, iter.y, 0xFF);
			++iter.x;
		}
		iter = (t_ivect2d){art->start.x, iter.y + 1};
	}
	return (NULL);
}

// void	draw_in_region()
// {

// }

void	split_draw(t_vars *vars, void *(*func)(void *), int nb_threads, t_ivect2d size, t_ivect2d pos)
{
	int	rg_width = size.x / nb_threads;
	int	rg_height = size.y;
	t_thread_artist art[nb_threads];
	pthread_t	threads[nb_threads];

	int i = 0;
	while (i < nb_threads)
	{
		art[i].vars = vars;
		art[i].start = (t_ivect2d){pos.x + i * rg_width, pos.y};
		art[i].end = (t_ivect2d){pos.x + (i + 1) * rg_width, pos.y + rg_height};
		pthread_create(threads + i, NULL, func, art + i);
		++i;
	}
	i = 0;
	while (i < nb_threads)
		pthread_join(threads[i++], NULL);
}

void	draw_background(t_vars *vars)
{
	split_draw(vars, draw_skybox, 3, (t_ivect2d){vars->mlx->width, vars->mlx->height >> 1}, (t_ivect2d){0, 0});
	split_draw(vars, draw_floor, 3, (t_ivect2d){vars->mlx->width, vars->mlx->height >> 1}, (t_ivect2d){0, vars->mlx->height >> 1});

	// t_thread_artist	art;
	// pthread_t th_skybox;
	// pthread_t th_floor;

	// art = (t_thread_artist){
	// 	vars, {500, 0}, {500 + 500, 500}
	// };
	// pthread_create(&th_skybox, NULL, draw_skybox, &art);
	// pthread_create(&th_floor, NULL, draw_floor, vars);

	// pthread_join(th_skybox, NULL);
	// pthread_join(th_floor, NULL);

			// if (iter.y > vars->mlx->height / 2)
			// 	prot_put_pixel(vars->img, iter.x, iter.y, 0xFF * (2 * (double)(iter.y - (double)vars->mlx->height / 2) / vars->mlx->height));
}

void	*draw_flash_light(void *param)
{
	t_thread_artist *art = param;
	t_ivect2d		iter;
	mlx_texture_t	*tex;
	uint32_t		color;

	tex = ifelse(art->vars->light_status, art->vars->light_on, art->vars->light_off);
	iter = art->start;
	while (iter.y < art->end.y)
	{
		while (iter.x < art->end.x)
		{
			int y_tex = (tex->height) * iter.y / art->vars->mlx->height;
			int x_tex = (tex->width) * iter.x / art->vars->mlx->width;
			color = ((uint32_t *)tex->pixels)[y_tex * tex->width + x_tex];
			if (color & 0xFF)
				prot_put_pixel(art->vars->img, iter.x, iter.y, color);
			++iter.x;
		}
		iter = (t_ivect2d){art->start.x, iter.y + 1};
	}
	return (NULL);
}

// void	draw_flash_light(t_vars *vars)
// {
// 	t_ivect2d		iter;
// 	mlx_texture_t	*tex;
// 	uint32_t		color;

// 	tex = ifelse(vars->light_status, vars->light_on, vars->light_off);
// 	iter = (t_ivect2d){(1331 * (vars->mlx->width/WIDTH)), 757 * (vars->mlx->height/HEIGHT)};
// 	while (iter.y < vars->mlx->height)
// 	{
// 		while (iter.x < vars->mlx->width)
// 		{
// 			int y_tex = (tex->height) * iter.y / vars->mlx->height;
// 			int x_tex = (tex->width) * iter.x / vars->mlx->width;
// 			color = ((uint32_t *)tex->pixels)[y_tex * tex->width + x_tex];
// 			if (color & 0xFF)
// 				prot_put_pixel(vars->img, iter.x, iter.y, color);
// 			++iter.x;
// 		}
// 		iter = (t_ivect2d){0, iter.y + 1};
// 	}
// }

void	draw_foreground(t_vars *vars)
{
	// draw_flash_light(vars);
	split_draw(vars, draw_flash_light, 3, (t_ivect2d){vars->mlx->width - 1331, vars->mlx->height - 737}, (t_ivect2d){1331, 737});
	// draw_flash_light(vars);
}
