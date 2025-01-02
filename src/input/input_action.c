/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:08:58 by mbico             #+#    #+#             */
/*   Updated: 2025/01/02 13:16:47 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	cam(t_data *data)
{
	if (get_input_state(data->input, 79))
	{
		data->player.dir += PI / 75 * data->player.rot_speed;
		while (data->player.dir > 2 * PI)
			data->player.dir -= PI * 2;
	}
	if (get_input_state(data->input, 80))
	{
		data->player.dir -= PI / 75 * data->player.rot_speed;
		while (data->player.dir < 0)
			data->player.dir += PI * 2;
	}
}

void	windows_input(t_data *data)
{
	if (get_input_state(data->input, 41))
		close_safe(data);
}

void	hud_action(t_data *data, int kc)
{
	if (kc == 17)
		data->hud.rotate_mm = !data->hud.rotate_mm;
}

int	key_action(t_data *data)
{
	windows_input(data);
	move(data);
	cam(data);
	return (0);
}
