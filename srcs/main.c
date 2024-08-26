/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:22:45 by mbico             #+#    #+#             */
/*   Updated: 2024/08/25 14:07:31 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_close(int keycode, t_data *data)
{
	print_background(data);
	put_wall(data, data->wall, data->cam);
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 119)
		data->cam.x += 0.1;
	else if (keycode == 115)
		data->cam.x -= 0.1;
	else if (keycode == 100)
		data->cam.y += 0.1;
	else if (keycode == 97)
		data->cam.y -= 0.1;
	else if (keycode == 114)
	{
		data->cam.x = 1;
		data->cam.y = 1;
	}
	return (0);
}

int	ft_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	put_wall(data, data->wall, data->cam);
	sleep(0);
	return (0);
}

int	main(void)
{
	t_data	data[1];

//=====================TRUC DEGUEU================================
	t_coord	wall[18];
	t_coord	cam;
	
	cam.x = 1;
	cam.y = 1;
	
	//xxxxx
	//xP..x
	//x..xx
	//x...x
	//xxxxx

	wall[0].x = 0; 
	wall[0].y = 0; 
	
	wall[1].x = 1; 
	wall[1].y = 0;

	wall[2].x = 2; 
	wall[2].y = 0; 
	
	wall[3].x = 3; 
	wall[3].y = 0; 
	
	wall[4].x = 4; 
	wall[4].y = 0; 
	
	wall[5].x = 0; 
	wall[5].y = 1; 
	
	wall[6].x = 4; 
	wall[6].y = 1; 
	
	wall[7].x = 0; 
	wall[7].y = 2; 
	
	wall[8].x = 3; 
	wall[8].y = 2; 
	
	wall[9].x = 4; 
	wall[9].y = 2; 
	
	wall[10].x = 0; 
	wall[10].y = 3; 
	
	wall[11].x = 4; 
	wall[11].y = 3; 
	
	wall[12].x = 0; 
	wall[12].y = 4; 
	
	wall[13].x = 1; 
	wall[13].y = 4; 
	
	wall[14].x = 2; 
	wall[14].y = 4; 
	
	wall[15].x = 3; 
	wall[15].y = 4; 
	
	wall[16].x = 4; 
	wall[16].y = 4; 
	
	wall[17].x = -1; 
	
	data->wall = wall;
	data->cam = cam;
	
//================================================================

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	print_background(data);
	mlx_hook(data->win, 2, 1L<<0, ft_close, &data);
	mlx_loop_hook(data->mlx, &ft_loop, data);
	mlx_loop(data->mlx);
}