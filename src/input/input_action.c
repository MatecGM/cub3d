/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:08:58 by mbico             #+#    #+#             */
/*   Updated: 2024/12/14 22:07:19 by mbico            ###   ########.fr       */
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

void	interact_system(t_data *data, int kc)
{
	t_wh		wh;
	t_wall		target;

	if (kc == 8)
	{
		wh = dda(data, data->player.dir);
		target = data->map.content[wh.rpos.y][wh.rpos.x];
		if (target == DOOR_CLS)
			data->map.content[wh.rpos.y][wh.rpos.x] = DOOR_OP;
		else if (target== DOOR_OP)
			data->map.content[wh.rpos.y][wh.rpos.x] = DOOR_CLS;
		else if (target == SPEAKER_OFF)
		{
			mutex_set_int(data->hud.mu_code, 1, &data->hud.mumu_code);
			data->hud.start_anim = time_now();
			data->map.content[wh.rpos.y][wh.rpos.x] = SPEAKER_ON;
		}
		else if (target== SPEAKER_ON)
		{
			if (get_speaker_coord(data->map, 0).x == -1)
				mutex_set_int(data->hud.mu_code, 0, &data->hud.mumu_code);
			data->map.content[wh.rpos.y][wh.rpos.x] = SPEAKER_OFF;
		}
	}
}

int	key_action(t_data *data)
{
	windows_input(data);
	move(data);
	cam(data);
	return (0);
}
