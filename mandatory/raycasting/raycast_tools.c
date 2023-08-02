/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:08:51 by yajallal          #+#    #+#             */
/*   Updated: 2023/08/02 23:17:10 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	calc_dis(t_coord hit, t_coord p)
{
	double	dis;

	dis = sqrt(pow(hit.x - p.x, 2) + pow(hit.y - p.y, 2));
	return (dis);
}

float	normlize_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}
