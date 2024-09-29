/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keydown.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:46:09 by mbico             #+#    #+#             */
/*   Updated: 2024/09/29 11:27:58 by mbico            ###   ########.fr       */
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
	if (kc == 26)
	{
		data->pos.x += data->rc.ax / 10;
		data->pos.y += data->rc.ay / 10;
	}
	if (kc == 22)
	{
		data->pos.x -= data->rc.ax / 10;
		data->pos.y -= data->rc.ay /10;
	}
	if (kc == 7)
		data->dir += PI/16;
	if (kc == 4)
		data->dir -= PI/16;
	data->rc.ax = cos(data->dir);
	data->rc.ay = sin(data->dir);
	displaying(data);
	return (0);
}


