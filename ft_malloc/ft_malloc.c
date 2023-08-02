/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:09:14 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/02 22:37:30 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_malloc(size_t size, int mode, char type)
{
	static t_malloc	*list_address;
	void			*address;

	if (mode == 1)
	{
		address = malloc(size);
		if (!address)
			return (NULL);
		list_address = add_new_node_malloc(address, type, list_address);
		return (address);
	}
	else if (mode == 0)
	{
		if (type == 'B' || type == 'A')
			list_address = delete_addr_before_after(list_address, type);
		else
			list_address = delete_addr(list_address);
	}
	return (NULL);
}
