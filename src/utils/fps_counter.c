/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:55:22 by mbico             #+#    #+#             */
/*   Updated: 2024/11/20 20:04:13 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	fps_counter(t_data *data)
{
	data->fps.old_time = data->fps.time;
	data->fps.time = time_now();
	data->fps.fps = 1000.0 / (data->fps.time - data->fps.old_time);
	/* printf("fps : %f\n", data->fps.fps); */
	data->player.move_speed = 1. / data->fps.fps * 130.;
	data->player.rot_speed = 1. / data->fps.fps * 50.;
}
