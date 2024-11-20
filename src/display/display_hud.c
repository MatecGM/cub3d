/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hud.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:03:18 by mbico             #+#    #+#             */
/*   Updated: 2024/11/17 18:16:27 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	display_crosshair(t_data *data)
{
	int		ptr;
	t_argb	color;

	ptr = HEIGHT / 2 - 4;
	while (ptr < HEIGHT / 2 + 5)
	{
		color.argb = 0xFF000000 | ~data->screen[ptr][WIDTH / 2];
		put_pixel_inscreen(data, WIDTH / 2, ptr, color);
		ptr ++;
	}
	ptr = WIDTH / 2 - 4;
	while (ptr < WIDTH / 2 + 5)
	{
		color.argb = 0xFF000000 | ~data->screen[HEIGHT / 2][ptr];
		put_pixel_inscreen(data, ptr, HEIGHT / 2, color);
		ptr ++;
	}	
}
