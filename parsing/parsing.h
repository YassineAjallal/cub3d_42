/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:38:46 by yajallal          #+#    #+#             */
/*   Updated: 2023/06/02 17:37:46 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>

#define pi 3.1415926535

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void error_print(char *error_msg);

typedef struct s_player
{
	int		x;
	int		y;
	float	v;
} t_player;

typedef struct s_map
{
	char *line;
	char cnofig;
	struct s_map *next;

} t_map;

char	*get_next_line(int fd);
char	*ft_read(int fd, char *save);
char	*ft_copy(char *save);
char	*ft_getnews(char *save);

t_map	*delete_node(t_map *head, char *str);
t_map *add_new_node(char *line, char config,t_map *map);


int ft_strchr2d(char **str2d, char *str);
void config_len(t_map *map);
t_map *config_list(char **split);
void check_map_config(t_map *map);

void print(t_map *map);

int	get_map_len(t_map *map);
char **get_map(t_map *map);

int ft_strlen2d(char **str);

int check_walls(char *line);
int check_empty_line(char *line);
int check_characters(char **map);
int first_last_wall(char *line);
int space_border(char **map, int i, int j);
int map_closed(char **map);
int check_valid_map(char **map);
#endif
