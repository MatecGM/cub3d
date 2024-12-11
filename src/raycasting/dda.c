/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:29:17 by mbico             #+#    #+#             */
/*   Updated: 2024/12/11 18:40:32 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <math.h>

static t_bool	in_map(t_dcoord size, t_coord p)
{
	return (p.x >= 0 && p.x < size.x && p.y >= 0 && p.y < size.y);
}

t_dcoord	get_cdvec(double dir)
{
	t_dcoord	cdvec;

	cdvec.x = 0;
	if (dir >= PI / 2 && dir < (3 * PI) / 2)
		cdvec.x = -1;
	cdvec.y = 0;
	if (dir > PI)
		cdvec.y = -1;
	return (cdvec);
}

t_wh	get_rel_pos(t_wh wh, int x, int y)
{
	wh.rpos.x = x;
	wh.rpos.y = y;
	return (wh);
}

t_wh	dda(t_data *data, double dir)
{
	t_coord	dist;
	t_coord	px;
	t_coord	py;
	t_wh	wh;

	px = dda_x(data, dir);
	py = dda_y(data, dir);
	dist.x = pow(px.x - data->player.pos.x, 2) \
	+ pow(px.y - data->player.pos.y, 2);
	dist.y = pow(py.x - data->player.pos.x, 2) \
	+ pow(py.y - data->player.pos.y, 2);
	wh.hit = px;
	wh.face = (dir < PI);
	if (in_map(data->map.size, px))
		wh = get_rel_pos(wh, px.x, px.y + get_cdvec(dir).y);
	if ((dist.x > dist.y && !check_approx(dist.y, 0.0, 1000000))
		|| check_approx(dist.x, 0.0, 1000000))
	{
		wh.face = (dir < PI / 2 || dir > 3 * PI / 2) + 2;
		wh.hit = py;
		if (in_map(data->map.size, py))
			wh = get_rel_pos(wh, py.x + get_cdvec(dir).x, py.y);
	}
	return (wh);
}
