/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:34:46 by mbico             #+#    #+#             */
/*   Updated: 2024/11/10 04:55:39 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	displaying(t_data *data)
{
	display_clear(data);
	//display_rc(data);
	display_map_mm(data);
	display_player_mm(data);
}

int	cube3d(void *d)
{
	t_data *data;

	data = (t_data *) d;
	key_action(data);
	displaying(data);
}

int	main(void)
{
	t_data		data[1];
	t_parse		psg[1];
	t_coord		pos;

	data->map_height = 15;
	data->map_width = 15;
	pos.x = 6;
	pos.y = 6;
	
	if (parsing("maps/test_square.cub", psg))
		return (1);
	data->psg = psg;
	data->map = psg->map;
	data->pos = pos;
	data->dir = convert_card_to_grad(psg->card);
	data->input = 0;
//================================================================

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_on_event(data->mlx, data->win, 	MLX_KEYDOWN, keydown, data);
	mlx_on_event(data->mlx, data->win, 	MLX_KEYUP, keyup, data);
	mlx_loop_hook(data->mlx, cube3d, data);
	displaying(data);
	mlx_loop(data->mlx);
}
