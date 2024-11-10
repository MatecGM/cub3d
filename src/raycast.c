/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:29:17 by mbico             #+#    #+#             */
/*   Updated: 2024/11/10 04:38:06 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <math.h>

t_coord	get_first_wall_x(t_data *data, double dir)
{
	double	ry;
	double	rx;
	double	yo;
	double	xo;

	int	dof = 0;
	double atan = -1/tan(dir);
	if (dir > PI)
	{
		ry = (int)data->pos.y;
		rx = (data->pos.y - ry) * atan + data->pos.x;
		yo = -1;
		xo = yo/tan(dir);
	}
	if (dir < PI)
	{
		ry = (int)data->pos.y + 1;
		rx = (data->pos.y - ry) * atan + data->pos.x;
		yo = 1;
		xo = yo/tan(dir);	
	}
	if (check_approx(dir, 0, 1000000) || check_approx(dir, PI, 1000000))
	{
		rx = data->pos.x;
		ry = data->pos.y;
		dof = 8;
	}
	while (dof < 8)
	{
		if (rx < data->map_width && rx >= 0 && ry < data->map_height && ry > 0 && (data->psg->map[(int)ry - (yo < 0)][(int)rx] ))
			dof = 8;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	t_coord p;
	p.x = rx;
	p.y = ry;
	return (p);

}

t_coord	get_first_wall_y(t_data *data, double dir)
{
	double	ry;
	double	rx;
	double	yo;
	double	xo;

	int	dof = 0;
	double atan = -tan(dir);
	if (dir > PI/2 || dir < 3 * PI / 2)
	{
		rx = (int)data->pos.x;
		ry = (data->pos.x - rx) * atan + data->pos.y;
		xo = -1;
		yo = -xo/tan(dir - PI / 2);
	}
	if (dir < PI / 2.0 || dir > 3 * PI / 2.0)
	{
		rx = (int)data->pos.x + 1;
		ry = (data->pos.x - rx) * atan + data->pos.y;
		xo = 1;
		yo = -xo/tan(dir - PI / 2);	
	}
	if (check_approx(dir, PI / 2.0, 1000000) || check_approx(dir, 3 * PI / 2.0, 1000000))
	{
		rx = data->pos.x;
		ry = data->pos.y;
		dof = 8;
	}
	while (dof < 8)
	{
		if (rx < data->map_width && rx >= 0 && ry < data->map_height && ry > 0 && (data->psg->map[(int)ry][(int)rx - (xo < 0)] ))
			dof = 8;
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	t_coord p;
	p.x = rx;
	p.y = ry;
	return (p);
}

t_coord	get_first_wall(t_data *data, double dir)
{
	t_coord	dist;
	t_coord	px;
	t_coord	py;

	px = get_first_wall_x(data, dir);
	py = get_first_wall_y(data, dir);
	dist.x = pow(px.x - data->pos.x, 2) + pow(px.y - data->pos.y, 2);
	dist.y = pow(py.x - data->pos.x, 2) + pow(py.y - data->pos.y, 2);
	if ((dist.x > dist.y && !check_approx(dist.y, 0.0, 1000000)) || check_approx(dist.x, 0.0, 1000000))
		return (py);
	return (px);
}


