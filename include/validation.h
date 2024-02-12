/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:01:26 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/12 17:34:45 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H
# include <parse.h>
# include <structs.h>
# define ll long long

int		validator(t_vars *vars);
size_t	count_object(t_map *map, int object);
size_t	count(const int *line, const int width, int c);
size_t	count_col(const int *col, const int width, const int height, int c);
size_t	count_players(t_map *map);
int		check_for_invalid_characters(t_map *map);
int		validate_map(t_map *map);
int		validate_line(int *line, int width);
void	register_player_pos(t_vars *vars, t_map *map);
bool	line_space_or_wall(int *line, size_t width, size_t height);
bool	col_space_or_wall(int *line, size_t width, size_t height);
bool	test_set_horizontal(t_map *map, int *first_line, int *last_line);
bool	test_set_vertical(t_map *map, int *first_col, int *last_col);
#endif
