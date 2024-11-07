/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_rc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 03:45:30 by mbico             #+#    #+#             */
/*   Updated: 2024/10/30 19:52:01 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cube3d.h>

int	get_wall_size(t_coord pos, t_coord hit)
{
	double	dist;
	int	size;
	

	dist = sqrt(pow(hit.x - pos.x, 2.0) + pow(hit.y - pos.y, 2.0));
	size = 1 / (double)dist * (HEIGHT / 2.0);
	return (size);
}

void	display_wall(t_data *data, int x, int size)
{
	int	y;
	int end;

	y = HEIGHT / 2 - size / 2;
	end = HEIGHT / 2 + size / 2;
	while (y < end)
	{
		mlx_set_image_pixel(data->mlx, data->img, x, y, 0xFFFFA500);
		y ++;
	}
}

void	display_rc(t_data *data)
{
	int		i;
	int		size;
	double	dir;
	t_coord	hit;

	i = 1;
	while (i < WIDTH)
	{
		dir = (data->dir - PI / 4.0) + ((PI / 2.0) / (double)WIDTH * i);
		if (dir < 0)
			dir += 2 * PI;
		else if (dir >= PI * 2)
			dir -= 2 * PI;
		hit = get_first_wall(data, dir);
		size = get_wall_size(data->pos, hit);
		display_wall(data, i, size);
		i ++;
	}
}
