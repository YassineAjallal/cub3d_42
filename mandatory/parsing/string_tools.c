/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:06:24 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 09:50:56 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	*ft_calloc_tool(size_t count, size_t size, char type)
// {
// 	void	*mem;

// 	mem = (void *)ft_malloc(count * size, 1, type);
// 	if (!mem)
// 		return (NULL);
// 	ft_bzero(mem, count * size);
// 	return (mem);
// }

// char	*ft_strdup_tool(const char *s1, char type)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	str = (char *)ft_malloc(ft_strlen(s1) + 1, 1, type);
// 	if (!str)
// 		return (NULL);
// 	while ((unsigned char)s1[i] != '\0')
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_strjoin_tool(char const *s1, char const *s2, char type)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	if (!s1)
// 		s1 = "";
// 	str = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1, type);
// 	if (!str)
// 		return (NULL);
// 	j = 0;
// 	while (s1 && s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	while (s2 && s2[j])
// 	{
// 		str[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_substr_tool(char const *s, unsigned int start, size_t len, char type)
// {
// 	char			*str;
// 	unsigned int	i;
// 	size_t			length;

// 	i = 0;
// 	length = ft_strlen(s);
// 	if (start >= length)
// 		return (ft_calloc_tool(sizeof(char), 1, type));
// 	if (len > length)
// 		len = length - start;
// 	str = (char *)ft_malloc(len + 1, 1, type);
// 	if (!str)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		str[i] = s[start + i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }
// char	*ft_strtrim_tool(char const *s1, char const *set, char type)
// {
// 	char	*str;
// 	size_t	len;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	len = ft_strlen(s1);
// 	tmp = (char *)set;
// 	if (!set || !s1)
// 		return (NULL);
// 	while (s1[i] && ft_strchr(tmp, s1[i]))
// 	{
// 		tmp = (char *)set;
// 		i++;
// 	}
// 	tmp = (char *)set;
// 	while (len > 0 && ft_strchr(tmp, s1[len - 1]))
// 	{
// 		tmp = (char *)set;
// 		len--;
// 	}
// 	str = ft_substr_tool(s1, i, len - i, type);
// 	return (str);
// }

// char	**ft_split_tool(char const *s, char c, char type)
// {
// 	char			**str;
// 	unsigned int	i;
// 	int				j;

// 	i = 0;
// 	j = 0;
// 	str = (char **)ft_malloc((ft_nbword((char *)s, c) + 1) * sizeof(char *), 1, type);
// 	if (!str)
// 		return (NULL);
// 	while (s[i] != '\0')
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i] != '\0')
// 		{
// 			str[j] = ft_substr_tool(s, i, ft_len((char *)s, c, i), type);
// 			j++;
// 			while (s[i] != c && s[i] != '\0')
// 				i++;
// 		}
// 	}
// 	str[j] = NULL;
// 	return (str);
// }