/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:29:17 by mbico             #+#    #+#             */
/*   Updated: 2024/10/07 00:43:57 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <math.h>

t_coord	get_diag_dir(t_data *data)
{
	double	ry;
	double	rx;
	double	yo;
	double	xo;

	int	dof = 0;
	double atan = -1/tan(data->dir);
	if (data->dir > PI)
	{
		ry = (int)data->pos.y;
		rx = (data->pos.y - ry) * atan + data->pos.x;
		yo = -1;
		xo = -yo / atan;
	}
	if (data->dir < PI)
	{
		ry = (int)data->pos.y + 1;
		rx = (data->pos.y - ry) * atan + data->pos.x;
		yo = 1;
		xo = -yo / atan;
	}
	if (((int)(data->dir*1000)) / 1000.0 == 0.0 || ((int)(data->dir*1000))  == ((int)(PI*100000)) / 100000)
	{
		rx = 0;//data->pos.x;
		ry = 0;//data->pos.y;
		printf("hit\n");
		dof = 8;
	}
	while (dof < 8)
	{
		if (rx < data->map_width && rx >= 0 && ry < data->map_height && ry > 0 && data->map[(int)ry][(int)rx])
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
	printf("%f %f et %f\n", rx, ry, data->dir);
	return (p);

}

