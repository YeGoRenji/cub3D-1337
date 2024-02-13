/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:31:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/13 02:44:22 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <MLX42/MLX42.h>
# include <maths.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define WIDTH 1920
# define HEIGHT 1080

# define ll long long

# define THREADS 8

# define TILE_W 25
# define TILE_COL_WALL 0x69FFFFFF
# define TILE_COL_EMPTY 0xFF69FFFF
# define TILE_COL_DOOR 0xFFFF69FF
# define MINIMAP_BORDER 0x202020FF
# define MINIMAP_WIDTH 300

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
	WEST,
	DOOR_TEX
}					t_orientation;

enum
{
	WE,
	NS
};

typedef enum block_type
{
	EMPTY,
	WALL,
	DOOR,
	SPACE = 9
}					t_block_type;

// ! Remove This
typedef struct s_dir
{
	int				x;
	int				y;
	int				is_flipped;
}					t_dir;

typedef struct s_color
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_color;

typedef struct s_player
{
	t_vect2d		pos;
	t_vect2d		dir;
}					t_player;

typedef struct s_surroundings
{
	int				ceiling;
	int				floor;
	int				ceiling_set;
	int				floor_set;
}					t_surroundings;

typedef struct s_map
{
	int				fd;
	size_t			height;
	size_t			width;
	int				*data;
	char			*tex[5];
	t_surroundings	colors;
}					t_map;

typedef struct s_vars
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	double			look_angle;
	int				fov;
	int				nb_vert_stripes;
	int				tile_size;
	t_map			map;
	t_ivect2d		mouse;
	int				pitch;
	mlx_texture_t	*nletter_tex;
	mlx_texture_t	*wall_tex[4];
	mlx_texture_t	*door_tex;
	mlx_texture_t	*sky_tex;
	mlx_texture_t	*light_off;
	mlx_texture_t	*light_on;
	bool			light_status;
	bool			mouse_locked;
}					t_vars;

typedef struct s_rayhit
{
	t_vect2d		where;
	double			dist;
	t_orientation	side;
	t_ivect2d		map;
	double			pos_in_texture;
	t_block_type	hit_what;
}					t_rayhit;

typedef t_ivect2d t_ivector;
typedef t_vect2d t_vector;

void				do_graphics(t_vars *vars);

#endif
