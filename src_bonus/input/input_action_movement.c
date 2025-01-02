/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_action_movement.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:16:47 by gadelbes          #+#    #+#             */
/*   Updated: 2025/01/02 14:49:41 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <cube3d.h>

t_coord	get_move_add(t_data *data, t_verif face, int c)
{
	t_coord	pos;
	int		sign;
	double	dir;

	sign = 1;
	pos = data->player.pos;
	if (face == SO || face == WE)
		sign = -1;
	if (face >= WE)
	{
		dir = data->player.dir + (PI / 2.0) * sign;
		pos.x += cos(dir) * data->player.move_speed / 100. * c;
		pos.y += sin(dir) * data->player.move_speed / 100. * c;
	}
	else
	{
		pos.x += (data->rc.ax / 50.0) * (double)sign * (double)c;
		pos.y += (data->rc.ay / 50.0) * (double)sign * (double)c;
	}
	if (pos.x < 0 || pos.x >= data->map.size.x || pos.x < 0
		|| pos.y >= data->map.size.y)
		pos = data->player.pos;
	return (pos);
}

double	get_rad_with_face(double rad, t_verif face)
{
	if (face == NO)
		return (rad);
	if (face == EA)
		rad = rad - (3 * PI / 2);
	else if (face == SO)
		rad = rad - PI;
	else if (face == WE)
		rad = rad - (PI / 2);
	while (rad < 0)
		rad += 2 * PI;
	return (rad);
}

double	check_collide(t_data *data, t_verif face)
{
	double	rad;
	t_wh	wh;
	double	dist;
	double	step;

	step = 1;
	rad = get_rad_with_face(data->player.dir, face);
	wh = dda(data, rad);
	dist = sqrt(pow(data->player.pos.x - wh.hit.x, 2) + pow(data->player.pos.y
				- wh.hit.y, 2));
	if (dist < 0.3 && data->map.content[wh.rpos.y][wh.rpos.x] != DOOR_OP)
		step = dist - 0.3;
	return (step);
}

void	move(t_data *data)
{
	int32_t	step;

	if (get_input_state(data->input, 26))
	{
		step = check_collide(data, NO);
		data->player.pos = get_move_add(data, NO, step);
	}
	if (get_input_state(data->input, 22))
	{
		step = check_collide(data, SO);
		data->player.pos = get_move_add(data, SO, step);
	}
	if (get_input_state(data->input, 7))
	{
		step = check_collide(data, EA);
		data->player.pos = get_move_add(data, EA, step);
	}
	if (get_input_state(data->input, 4))
	{
		step = check_collide(data, WE);
		data->player.pos = get_move_add(data, WE, step);
	}
	data->rc.ax = cos(data->player.dir) * data->player.move_speed;
	data->rc.ay = sin(data->player.dir) * data->player.move_speed;
}
