/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keydown.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:46:09 by mbico             #+#    #+#             */
/*   Updated: 2024/10/11 02:33:05 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int ft_keydown(int kc, void *d)
{
	t_data	*data;

	data = (t_data *)d;
	if (kc == 41)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_display(data->mlx);
		exit(EXIT_SUCCESS);
	}
	else if (kc == 26)
	{
		data->pos.x += data->rc.ax / 15;
		data->pos.y += data->rc.ay / 15;
	}
	else if (kc == 22)
	{
		data->pos.x -= data->rc.ax / 15;
		data->pos.y -= data->rc.ay / 15;
	}
	else if (kc == 7)
	{
		data->dir += PI/16;
		if (data->dir > 2 * PI)
			data->dir -= PI * 2;
	}
	else if (kc == 4)
	{
		data->dir -= PI/16;
		if (data->dir < 0)
			data->dir += PI * 2;
	}
	data->rc.ax = cos(data->dir) * 5;
	data->rc.ay = sin(data->dir) * 5;
	displaying(data);
	return (0);
}


