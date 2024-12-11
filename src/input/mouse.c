/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:54:55 by mbico             #+#    #+#             */
/*   Updated: 2024/12/11 18:18:38 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cube3d.h>

int	mousedown(int kc, void *d)
{
	t_data	*data;

	data = (t_data *)d;
	mlx_mouse_hide();
	if (kc == 3)
	{
		data->player.old_dir = data->player.dir;
		mlx_mouse_get_pos(data->mlx, &data->player.mouse_init.x,
			&data->player.mouse_init.y);
	}
	data->input |= ((__uint128_t)1 << kc);
	return (0);
}

int	mouseup(int kc, void *d)
{
	t_data	*data;

	data = (t_data *)d;
	mlx_mouse_show();
	data->input &= ~((__uint128_t)1 << kc);
	return (0);
}
