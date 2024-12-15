/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:55:22 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 18:45:32 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	fps_counter(t_data *data)
{
	data->fps.old_time = data->fps.time;
	data->fps.time = time_now();
	data->fps.fps = 1000.0 / (data->fps.time - data->fps.old_time);
	data->player.move_speed = 1. / data->fps.fps * 130.;
	data->player.rot_speed = 1. / data->fps.fps * 50.;
}
