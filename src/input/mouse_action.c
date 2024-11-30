/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:01:04 by mbico             #+#    #+#             */
/*   Updated: 2024/11/28 00:36:55 by mbico            ###   ########.fr       */
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
	data->player.dir = pl.old_dir - (PI / 270) * (pl.mouse_init.x - m.x);
	while (data->player.dir > 2 * PI)
		data->player.dir -= PI * 2;
	while (data->player.dir < 0)
		data->player.dir += PI * 2;

}

void	mouse_action(t_data *data)
{
	if (get_input_state(data->input, 3))
		mouse_direction(data);
}
