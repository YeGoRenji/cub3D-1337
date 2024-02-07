/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:31:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/07 16:36:51 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdbool.h>
# include <stdio.h>
# include <maths.h>
# include <pthread.h>
# include <unistd.h>
# include <MLX42/MLX42.h>

# define WIDTH 1920
# define HEIGHT 1080

# define TILE_W 25
# define TILE_COL_1 0x69FFFFFF
# define TILE_COL_2 0xFF69FFFF
# define TILE_COL_3 0xFFFF69FF
# define MINI_MAP_BORDER 0x202020FF
# define MINI_MAP_WIDTH 300

# define FPS_COLOR 0xFF6942FF

// ! REMOVE THIS
# define OLD_MAP_2D 0xAA50AAFF

# define MVT_SPEED 2
# define ROT_SPEED 2

typedef enum orientation
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_orientation;

enum
{
	WE,
	NS
};

typedef enum block_type 
{
	EMPTY,
	WALL,
	DOOR
}	t_block_type;

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

typedef struct s_player
{
	t_vect2d	pos;
	t_vect2d	dir;
}				t_player;

typedef struct s_map
{
	int		width;
	int		height;
	int		*data;
}				t_map;

typedef struct s_vars
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	double		look_angle;
	int 		fov;
	int 		nb_vert_stripes;
	int			tile_size;
	t_map		map;
	t_ivect2d	mouse;
	mlx_texture_t *nletter_tex;
	mlx_texture_t *wall_tex[4];
	mlx_texture_t *door_tex;
	mlx_texture_t *sky_tex;
	mlx_texture_t *light_off;
	mlx_texture_t *light_on;
	bool			light_status;
}				t_vars;

typedef struct s_rayhit
{
	t_vect2d		where;
	double			dist;
	t_orientation	side;
	t_ivect2d		map;
	double			pos_in_texture;
	t_block_type	hit_what;
}				t_rayhit;

#endif
