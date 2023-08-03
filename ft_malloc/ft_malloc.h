/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:34:52 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/03 19:13:14 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_malloc
{
	void			*address;
	char			type;
	struct s_malloc	*next;
}					t_malloc;

void				*ft_malloc(size_t size, int mode, char type);

t_malloc			*add_new_node_malloc(void *address, char type,
						t_malloc *head);
t_malloc			*delete_addr(t_malloc *head);
t_malloc			*delete_addr_before_after(t_malloc *head, char type);
#endif
