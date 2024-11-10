/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:18:36 by mbico             #+#    #+#             */
/*   Updated: 2024/11/10 21:47:44 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx.h"

void	display_clear(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel_inscreen(data, x, y, 0xEEEEEEFF);
			x ++;
		}
		y ++;
	} 
}

void	put_pixel_inscreen(t_data *data, int x, int y, int color)
{
	if (x < WIDTH && x > 0 && y < HEIGHT && y > 0)
		data->screen[y][x] = color;
}

void	display_screen(t_data *data, int32_t **screen)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			mlx_set_image_pixel(data->mlx, data->img, x, y, screen[y][x]);
			x ++;
		}
		y ++;
	}
}
