/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 06:35:05 by mbico             #+#    #+#             */
/*   Updated: 2024/11/27 23:03:31 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	dda_x_hor_exept(t_rc *rc, t_coord pos, double dir)
{
	if (check_approx(dir, 0, 1000000) || check_approx(dir, PI, 1000000))
	{
		rc->ray.x = pos.x;
		rc->ray.y = pos.y;
		rc->rd = RENDER_DISTANCE;
	}
}

t_rc	dda_x_init(t_coord pos, double dir)
{
	t_rc	rc;
	double	atan;

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

	rc = dda_x_init(data->player.pos, dir);
	while (rc.rd < RENDER_DISTANCE)
	{
		if (rc.ray.x < data->map.size.x && rc.ray.x >= 0
			&& rc.ray.y < data->map.size.y && rc.ray.y > 0
			&& (data->psg->map[(int)rc.ray.y
					- (rc.side_dist.y < 0)][(int)rc.ray.x]))
			rc.rd = RENDER_DISTANCE;
		else
		{
			rc.ray.x += rc.side_dist.x;
			rc.ray.y += rc.side_dist.y;
			rc.rd += 1;
		}
	}
	return (rc.ray);
}
