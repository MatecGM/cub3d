/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keydown.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:46:09 by mbico             #+#    #+#             */
/*   Updated: 2024/11/10 04:26:02 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_bool	get_input_state(__uint128_t input, int kc)
{
	 return ((input >> kc) & 1);
}

int key_action(t_data *data)
{
	if (get_input_state(data->input, 41))
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_display(data->mlx);
		exit(EXIT_SUCCESS);
	}
	if (get_input_state(data->input, 26))
	{
		data->pos.x += data->rc.ax / 50;
		data->pos.y += data->rc.ay / 50;
	}
	if (get_input_state(data->input, 22))
	{
		data->pos.x -= data->rc.ax / 50;
		data->pos.y -= data->rc.ay / 50;
	}
	if (get_input_state(data->input, 7))
	{
		data->dir += PI/90;
		if (data->dir > 2 * PI)
			data->dir -= PI * 2;
	}
	if (get_input_state(data->input, 4))
	{
		data->dir -= PI/90;
		if (data->dir < 0)
			data->dir += PI * 2;
	}
	data->rc.ax = cos(data->dir) * 5;
	data->rc.ay = sin(data->dir) * 5;
	return (0);
}

int	keydown(int kc, void *d)
{
	t_data		*data;
	
	data = (t_data *)d;
	data->input |= ((__uint128_t)1 << kc);
	return (0);
}

int	keyup(int kc, void *d)
{
	t_data		*data;
	
	data = (t_data *)d;
	data->input &= ~((__uint128_t)1 << kc);
	return (0);
}
