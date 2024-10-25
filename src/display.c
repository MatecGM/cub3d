/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 03:45:30 by mbico             #+#    #+#             */
/*   Updated: 2024/10/11 04:17:22 by mbico            ###   ########.fr       */
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
