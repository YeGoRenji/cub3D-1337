/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:23:11 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/14 21:32:40 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <libft.h>
# include <stdlib.h>
# include <hooks.h>
# include <structs.h>

enum
{
	EAST_IN_MAP = 69,
	SOUTH_IN_MAP,
	WEST_IN_MAP,
	NORTH_IN_MAP,
	SPACE_IN_MAP = 9
};

typedef struct s_map_data
{
	t_map_line	*data;
	size_t		height;
	size_t		width;
}				t_map_data;

//# define DEBUG
bool			map_items_collected(t_map *map);
int				item_setter_dispatcher(t_map *m, char *line,
					char *where, char *what);
int				parser(t_vars *vars, char *file);
int				get_map_items(t_map *map);
int				count_chars(const char *s, int c);
int				check_extension(char *name, char *extension);
t_map			*init_map(char *file);
int				try_open_file(char *file, char *extension);
int				open_file(char *file);
int				get_map_parts(t_map *map);
int				get_textures(t_map *map);
int				set_map_texture(t_map *map, char *text, char *file);
int				set_map_colors(t_map *map, char *_obj, char *lgbt_colors);
size_t			get_list_len(char **l);
int				get_surroundings(t_map *_map);
int				validate_lgbt(char *_r, char *_g, char *_b);
int				check_digit_list(char **list);
uint32_t		construct_lgbt(char *r, char *g, char *b);
t_map_data		*read_map(t_map *map);
void			append_map_node(t_map_data *data, char *line);
int				*consume_map(t_map_data *m);
int				convert_map_char(char c);
void			set_where_and_flag(int **where, int **flag, int *w_val,
					int *f_val);
int				get_map_textures(t_map *map);
bool			check_textures(t_map *map);
bool			check_colors(t_map *map);
int				check_map_items(t_map *map);
#endif
