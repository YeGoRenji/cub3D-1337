/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:31:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/01/24 16:00:49 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdbool.h>
# include <maths.h>
# include <MLX42/MLX42.h>


typedef struct s_ivect2d
{
	int		x;
	int		y;
}				t_ivect2d;

typedef struct s_dir
{
	int	x;
	int	y;
	int	is_flipped;
}				t_dir;

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

typedef struct s_map {
	int		width;
	int		height;
	int		*data;
}				t_map;

typedef struct s_vars {
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	double		look_angle;
	int 		fov;
	int 		nb_vert_stripes;
	int			tile_size;
	t_map		map;
	t_ivect2d	mouse;
}				t_vars;


typedef struct s_rayhit {
	t_vect2d	where;
	double		dist;
	int			side;
	t_ivect2d	map;
	double		pos_in_texture;
}				t_rayhit;

#endif
