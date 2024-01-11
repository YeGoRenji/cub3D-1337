/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:31:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/11 02:45:40 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdbool.h>
# include <MLX42/MLX42.h>

typedef struct s_vect2d
{
	double		x;
	double		y;
}				t_vect2d;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}				t_color;

typedef struct s_player {
	t_vect2d	pos;
	t_vect2d	dir;
}				t_player;

typedef struct s_vars {
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
}				t_vars;

#endif
