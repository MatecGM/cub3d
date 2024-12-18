/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 04:57:51 by mbico             #+#    #+#             */
/*   Updated: 2024/12/18 20:36:11 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "ssys.h"
#include <cube3d.h>

void	displaying(t_data *data)
{
	t_coord	center;

	display_clear(data);
	display_rc(data);
	display_crosshair(data);
	display_mm(data);
	center.x = 120;
	center.y = 120;
	circle_mm(data, center, 75, (t_argb)0xFFFFFFFF);
	display_screen(data, data->screen);
}

int	cube3d(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	speaker_stereo(data);
	key_action(data);
	mouse_action(data);
	displaying(data);
	fps_counter(data);
	return (0);
}

void	free_arg(char **arg)
{
	if (*arg)
		free(*arg);
}

void	mlx_start(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, keydown, data);
	mlx_on_event(data->mlx, data->win, MLX_KEYUP, keyup, data);
	mlx_on_event(data->mlx, data->win, MLX_MOUSEUP, mouseup, data);
	mlx_on_event(data->mlx, data->win, MLX_MOUSEDOWN, mousedown, data);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_cross, data);
	mlx_loop_hook(data->mlx, cube3d, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data[1];
	t_parse	psg[1];
	uint8_t	mu_code;
	t_coord	mu_stereo;

	__attribute__((cleanup(free_arg))) char *arg;
	arg = NULL;
	if (argc == 2)
		arg = ft_strdup(argv[1]);
	if (!arg || argc != 2 || parsing(arg, psg))
	{
		ft_putstr_fd("Parsing init failed\n", 2);
		return (TRUE);
	}
	mu_code = 0;
	mu_stereo = (t_coord){0, 0};
	if (init_data(data, psg, &mu_code, &mu_stereo) || ssys_thread_init(data))
	{
		ft_putstr_fd("Data init failed\n", 2);
		close_safe(data);
		return (TRUE);
	}
	mlx_start(data);
	return (FALSE);
}
