/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:01:04 by mbico             #+#    #+#             */
/*   Updated: 2024/11/17 10:52:59 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cube3d.h>

void	mouse_direction(t_data *data)
{
	t_dcoord	m;
	t_player	pl;

	mlx_mouse_get_pos(data->mlx, &m.x, &m.y);
	pl = data->player;
	data->player.dir = pl.old_dir - (PI / 180) * (pl.mouse_init.x - m.x);
}

void	mouse_action(t_data *data)
{
	if (get_input_state(data->input, 3))
		mouse_direction(data);
}
