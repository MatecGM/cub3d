/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:26:00 by mbico             #+#    #+#             */
/*   Updated: 2024/08/25 00:48:36 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_background(t_data *data)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_pixel_put(data->mlx, data->win, x, y, 0x00FF0000);
			else
				mlx_pixel_put(data->mlx, data->win, x, y, 0x0000FF00);
			x ++;
		}
		y ++;
		x = 0;
	}
}
