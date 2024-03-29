/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:38:46 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 16:20:25 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../structs.h"

void	config_len(t_map *map);
t_map	*config_list(char **split);
int		array_len(char **array);
int		allint(char **a, t_map *map);
int		color_formatting(char *color);
void	check_map_config(t_map *map, t_cub *game);
void	check_valid_color(t_map *map, t_cub *game);

int		check_walls(char *line);
int		check_empty_line(char *line);
int		check_characters(char **map);
int		first_last_wall(char *line);
int		space_border(char **map, int i, int j);
int		map_closed(char **map);
int		check_valid_map(char **map);

void	error_print(char *error_msg);

int		get_map_len(t_map *map);
char	**get_map(t_map *map, t_cub *game);
int		get_large_line(t_cub *game);

char	*ft_read(int fd, char *save);
char	*ft_copy(char *save);
char	*ft_getnews(char *save);
char	*get_next_line(int fd);

t_map	*add_new_node(char *line, char config, t_map *map);
t_map	*delete_node(t_map *head, char *str);
t_map	*free_list(t_map *map);
size_t	lst_size(t_map *config);

void	print(t_map *map);
t_map	*read_map(char *map_file);

int		ft_strlen2d(char **str);
void	ft_free2d(char **str);
void	valid_extention(char *map_file);

char	**extract_textures(t_map *map);
#endif
