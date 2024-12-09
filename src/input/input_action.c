/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:08:58 by mbico             #+#    #+#             */
/*   Updated: 2024/12/09 19:51:13 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_coord	get_move_add(t_data *data, t_verif face, int c)
{
	t_coord	pos;
	int		sign;
	
	sign = 1;
	pos = data->player.pos;
	if (face == SO || face == WE)
		sign = -1;
	if (face >= WE)
	{
		pos.x += cos(data->player.dir + (PI / 2.0) * (double)sign) / 25.0 * c;
		pos.y += sin(data->player.dir + (PI / 2.0) * (double)sign) / 25.0 * c;
	}
	else
	{
		pos.x += (data->rc.ax / 50.0) * (double)sign * c;
		pos.y += (data->rc.ay / 50.0) * (double)sign * c;
	}
	return (pos);
}

t_bool	check_collide(t_data *data, t_verif face)
{
	t_coord		pos;
	int			sign;
	t_dcoord	coord;
	
	sign = 1;
	if (face == SO || face == WE)
		sign = -1;
	pos = get_move_add(data, face, 5);
	coord.x = (int)pos.x - (data->rc.side_dist.x < 0);
	coord.y = (int)pos.y - (data->rc.side_dist.y < 0);
	if (coord.y < 0 || coord.y > data->map.size.y || coord.x < 0 || coord.x > data->map.size.x || data->map.content[coord.y][coord.x] == 1 || data->map.content[coord.y][coord.x] == 2 || data->map.content[coord.y][coord.x] == 4 || data->map.content[coord.y][coord.x] == 5)
		return (TRUE);
	return (FALSE);
}

void	move(t_data *data)
{
	if (get_input_state(data->input, 26) && !check_collide(data, NO))
		data->player.pos = get_move_add(data, NO, 1);
	if (get_input_state(data->input, 22) && !check_collide(data, SO))
		data->player.pos = get_move_add(data, SO, 1);
	if (get_input_state(data->input, 7) && !check_collide(data, EA))
		data->player.pos = get_move_add(data, EA, 1);
	if (get_input_state(data->input, 4) && !check_collide(data, WE))
		data->player.pos = get_move_add(data, WE, 1);
	data->rc.ax = cos(data->player.dir) * data->player.move_speed;
	data->rc.ay = sin(data->player.dir) * data->player.move_speed;
}

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
			data->map.content[wh.rpos.y][wh.rpos.x] = SPEAKER_ON;
		else if (target== SPEAKER_ON)
		{
			data->hud.start_anim = time_now();
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
