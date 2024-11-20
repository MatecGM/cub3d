/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:29:17 by mbico             #+#    #+#             */
/*   Updated: 2024/11/17 20:44:24 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <math.h>

t_wh	dda(t_data *data, double dir)
{
	t_coord	dist;
	t_coord	px;
	t_coord	py;
	t_wh	wh;

	px = dda_x(data, dir);
	py = dda_y(data, dir);
	dist.x = pow(px.x - data->player.pos.x, 2) + pow(px.y - data->player.pos.y, 2);
	dist.y = pow(py.x - data->player.pos.x, 2) + pow(py.y - data->player.pos.y, 2);
	wh.hit = px;
	wh.face = (dir < PI);
	if ((dist.x > dist.y && !check_approx(dist.y, 0.0, 1000000))
		|| check_approx(dist.x, 0.0, 1000000))
	{
		wh.face = (dir < PI / 2 || dir > 3 * PI / 2) + 2;
		wh.hit = py;
	}
	return (wh);
}
