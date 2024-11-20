/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:08:58 by mbico             #+#    #+#             */
/*   Updated: 2024/11/20 13:11:17 by mbico            ###   ########.fr       */
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
	if (coord.y < 0 || coord.y > HEIGHT || coord.x < 0 || coord.x > WIDTH || data->map.content[coord.y][coord.x])
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
	data->rc.ax = cos(data->player.dir) * 5;
	data->rc.ay = sin(data->player.dir) * 5;
}

void	cam(t_data *data)
{
	if (get_input_state(data->input, 79))
	{
		data->player.dir += PI / 75;
		if (data->player.dir > 2 * PI)
			data->player.dir -= PI * 2;
	}
	if (get_input_state(data->input, 80))
	{
		data->player.dir -= PI / 75;
		if (data->player.dir < 0)
			data->player.dir += PI * 2;
	}
}

void	windows_input(t_data *data)
{
	if (get_input_state(data->input, 41))
		close_safe(data);
}

int	key_action(t_data *data)
{
	windows_input(data);
	move(data);
	cam(data);
	return (0);
}
