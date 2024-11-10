/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:29:17 by mbico             #+#    #+#             */
/*   Updated: 2024/11/10 23:40:03 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <math.h>

void	dda_x_hor_exept(t_rc *rc, t_coord pos, double dir)
{
	if (check_approx(dir, 0, 1000000) || check_approx(dir, PI, 1000000))
	{
		rc->ray.x = pos.x;
		rc->ray.y = pos.y;
		rc->rd = 8;
	}
}

t_rc	dda_x_init(t_coord pos, double dir)
{
	t_rc	rc;
	double atan;

	rc.rd = 0;
	atan = -1 / tan(dir);
	if (dir > PI)
	{
		rc.ray.y = (int)pos.y;
		rc.ray.x = (pos.y - rc.ray.y) * atan + pos.x;
		rc.side_dist.y = -1;
		rc.side_dist.x = rc.side_dist.y / tan(dir);
	}
	if (dir < PI)
	{
		rc.ray.y = (int)pos.y + 1;
		rc.ray.x = (pos.y - rc.ray.y) * atan + pos.x;
		rc.side_dist.y = 1;
		rc.side_dist.x = rc.side_dist.y / tan(dir);	
	}
	dda_x_hor_exept(&rc, pos, dir);
	return (rc);
}

t_coord	dda_x(t_data *data, double dir)
{
	t_rc	rc;
	
	rc = dda_x_init(data->pos, dir);
	while (rc.rd < 8)
	{
		if (rc.ray.x < data->map_width && rc.ray.x >= 0 && rc.ray.y < data->map_height && rc.ray.y > 0 && (data->psg->map[(int)rc.ray.y - (rc.side_dist.y < 0)][(int)rc.ray.x] ))
			rc.rd = 8;
		else
		{
			rc.ray.x += rc.side_dist.x;
			rc.ray.y += rc.side_dist.y;
			rc.rd += 1;
		}
	}
	return (rc.ray);
}

void	dda_y_vert_exept(t_rc *rc, t_coord pos, double dir)
{
	if (check_approx(dir, PI / 2.0, 1000000) || check_approx(dir, 3 * PI / 2.0, 1000000))
	{
		rc->ray.x = pos.x;
		rc->ray.y = pos.y;
		rc->rd = 8;
	}
}

t_rc	dda_y_init(t_coord pos, double dir)
{	
	t_rc	rc;
	double atan;

	rc.rd = 0;
	atan = -tan(dir);
	if (dir > PI / 2 || dir < 3 * PI / 2)
	{
		rc.ray.x = (int)pos.x;
		rc.ray.y = (pos.x - rc.ray.x) * atan + pos.y;
		rc.side_dist.x = -1;
		rc.side_dist.y = -rc.side_dist.x / tan(dir - PI / 2);
	}
	if (dir < PI / 2.0 || dir > 3 * PI / 2.0)
	{
		rc.ray.x = (int)pos.x + 1;
		rc.ray.y = (pos.x - rc.ray.x) * atan + pos.y;
		rc.side_dist.x = 1;
		rc.side_dist.y = -rc.side_dist.x / tan(dir - PI / 2);	
	}
	dda_y_vert_exept(&rc, pos, dir);
	return (rc);
}
t_coord	dda_y(t_data *data, double dir)
{
	t_rc	rc;
	
	rc = dda_y_init(data->pos, dir);
	while (rc.rd < 8)
	{
		if (rc.ray.x < data->map_width && rc.ray.x >= 0 && rc.ray.y < data->map_height && rc.ray.y > 0 && (data->psg->map[(int)rc.ray.y][(int)rc.ray.x - (rc.side_dist.x < 0)] ))
			rc.rd = 8;
		else
		{
			rc.ray.x += rc.side_dist.x;
			rc.ray.y += rc.side_dist.y;
			rc.rd += 1;
		}
	}
	return (rc.ray);
}

t_wh	dda(t_data *data, double dir)
{
	t_coord	dist;
	t_coord	px;
	t_coord	py;
	t_wh	wh;

	px = dda_x(data, dir);
	py = dda_y(data, dir);
	dist.x = pow(px.x - data->pos.x, 2) + pow(px.y - data->pos.y, 2);
	dist.y = pow(py.x - data->pos.x, 2) + pow(py.y - data->pos.y, 2);
	wh.hit = px;
	if ((dist.x > dist.y && !check_approx(dist.y, 0.0, 1000000)) || check_approx(dist.x, 0.0, 1000000))
	{
		wh.hit = py;
	}
	return (wh);
}


