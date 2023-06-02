/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/06/02 14:49:14 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"


void	move_player(t_player *player, int key)
{
	if(key == 0)
		player->x++;
	if(key == 2)
		player->x--;
	if(key == 1)
		player->y++;
	if(key == 13)
		player->y--;
	if(key == 123)
		player->v++;
	if(key == 124)
		player->v--;
}

void	ray_calc()
{
	
}
