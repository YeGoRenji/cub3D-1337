/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:21:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/10 04:00:25 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include <structs.h>
# include <stdio.h>
# include <stdlib.h>
# include <maths.h>
# include <input.h>

/* Entry func */
void	do_graphics(t_vars* vars);

void	draw_line(t_vars *vars, t_ivect2d pt1, t_ivect2d pt2, uint32_t color);
void	prot_put_pixel(mlx_image_t *image, int x, int y, uint32_t color);
void	clear_screen(t_vars* vars, uint32_t color);

/* Primitives */
void	draw_square(t_vars* vars, t_vect2d anchor, int width, uint32_t color);
void	draw_star(t_vars *vars, t_vect2d center, uint32_t color);
void	draw_trig(t_vars *vars, t_ivect2d pos, t_ivect2d size, uint32_t color);
void	draw_circle(t_vars *vars, t_ivect2d center, int radius, uint32_t color);
void	draw_texture(t_vars *vars, mlx_texture_t *texture, t_ivect2d pos);


/* Walls */
void	draw_wall_stripes(t_vars *vars);
int		get_map_val(t_vars *vars, int x, int y);

/* Mini map */
void draw_minimap(t_vars *vars, t_ivect2d pos);

/* Textures */
mlx_texture_t	*get_default_tex(void);
mlx_texture_t	*load_tex_png(const char *path);

/* Background/Foreground */
void	draw_background(t_vars *vars);
void	draw_foreground(t_vars *vars);

/* FPS COUNTER */
void	*fps_thread(void *param);
void	draw_fps(t_vars *vars);

/* Multi-Thread Drawing ~_~ */

typedef struct e_thread_artist {
	t_vars		*vars;
	t_ivect2d	start;
	t_ivect2d	end;
} t_thread_artist;

void	split_draw(t_vars *vars, void *(*func)(void *), t_ivect2d size, t_ivect2d pos);
#endif
