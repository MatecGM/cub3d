/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 04:57:51 by mbico             #+#    #+#             */
/*   Updated: 2024/12/11 16:07:37 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "ssys.h"
#include <cube3d.h>

void	displaying(t_data *data)
{
	display_clear(data);
	display_rc(data);
	display_crosshair(data);
	display_mm(data);
	t_coord center;
	center.x = 120;
	center.y = 120;
	circle_mm(data, center, 75, (t_argb)0xFFFFFFFF);
	display_screen(data, data->screen);
}

int	cube3d(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	key_action(data);
	mouse_action(data);
	displaying(data);
	fps_counter(data);
	return (0);
}

int	main(void)
{
	t_data	data[1];
	t_parse	psg[1];
	uint8_t	mu_code;
	t_coord	pos;

	mu_code = 0;
	if (init_data(data, psg, &mu_code))
		return (1);
	ssys_thread_init(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, keydown, data);
	mlx_on_event(data->mlx, data->win, MLX_KEYUP, keyup, data);
	mlx_on_event(data->mlx, data->win, MLX_MOUSEUP, mouseup, data);
	mlx_on_event(data->mlx, data->win, MLX_MOUSEDOWN, mousedown, data);
	mlx_loop_hook(data->mlx, cube3d, data);
	mlx_loop(data->mlx);
}
