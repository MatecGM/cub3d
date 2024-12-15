/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_y.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 06:34:10 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 17:15:40 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	dda_y_vert_exept(t_rc *rc, t_coord pos, double dir)
{
	if (check_approx(dir, PI / 2.0, 1000000) || check_approx(dir, 3 * PI / 2.0,
			1000000))
	{
		rc->ray.x = pos.x;
		rc->ray.y = pos.y;
		rc->rd = RENDER_DISTANCE;
	}
}

t_rc	dda_y_init(t_coord pos, double dir)
{
	t_rc	rc;
	double	atan;

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

	rc = dda_y_init(data->player.pos, dir);
	while (rc.rd < RENDER_DISTANCE)
	{
		if (rc.ray.x < data->map.size.x && rc.ray.x >= 0
			&& rc.ray.y < data->map.size.y && rc.ray.y > 0
			&& (data->psg->map[(int)rc.ray.y][(int)rc.ray.x
				- (rc.side_dist.x < 0)]))
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
