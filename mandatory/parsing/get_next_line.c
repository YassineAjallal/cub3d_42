/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 03:34:16 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/02 22:25:39 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_read(int fd, char *save)
{
	ssize_t	x;
	char	*tmp;
	char	*buff;

	x = 1;
	buff = ft_malloc(BUFFER_SIZE + 1, 1, 'B');
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	while (x > 0 && !ft_strchr(buff, '\n'))
	{
		x = read(fd, buff, BUFFER_SIZE);
		if (x < 0)
			return (NULL);
		buff[x] = '\0';
		tmp = ft_strjoin_tool(save, buff, 'A');
		save = tmp;
	}
	return (save);
}

char	*ft_copy(char *save)
{
	int		i;
	char	*line;

	i = 0;
	while (save[i] != '\n' && save[i])
		i++;
	line = ft_substr_tool(save, 0, i, 'A');
	return (line);
}

char	*ft_getnews(char *save)
{
	int		i;
	char	*tmp;
	char	*len;

	len = save;
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
	{
		i++;
		len++;
	}
	if (save[i] == '\n')
	{
		i++;
		len++;
	}
	tmp = ft_substr_tool(save, i, ft_strlen(len), 'B');
	save = tmp;
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd == 1 || fd == 2 || read(fd, 0, 0) < 0)
		return (NULL);
	save = ft_read(fd, save);
	if (!save)
		return (NULL);
	if (save[0] == '\0')
		return (NULL);
	line = ft_copy(save);
	save = ft_getnews(save);
	return (line);
}
