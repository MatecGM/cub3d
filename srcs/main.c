/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:22:45 by mbico             #+#    #+#             */
/*   Updated: 2024/09/20 09:32:12 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	ft_close(int keycode, void *d)
{
	t_data	*data;

	data = (t_data *)d;
	print_background(data);
	if (keycode == 41)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_display(data->mlx);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 21)
	{
		data->pos.x = 1;
		data->pos.y = 1;
	}
	if (keycode == 26)
    {
		data->pos.x += (data->raycast->dir.x + data->raycast->plane.x) / 3;
		data->pos.y += (data->raycast->dir.y + data->raycast->plane.y) / 3;
    }
    //move backwards if no wall behind you
    if (keycode == 22)
    {
		data->pos.x -= (data->raycast->dir.x + data->raycast->plane.x) / 3;
		data->pos.y -= (data->raycast->dir.y + data->raycast->plane.y) / 3;
    }
	if (keycode == 4)
    {
      //both camera direction and camera plane must be rotated
		double oldDirX = data->raycast->dir.x;
		data->raycast->dir.x = data->raycast->dir.x * cos(-PI/80) - data->raycast->dir.y * sin(-PI/80);
		data->raycast->dir.y = oldDirX * sin(-PI/80) + data->raycast->dir.y * cos(-PI/80);
		double oldPlaneX = data->raycast->plane.x;
		data->raycast->plane.x = data->raycast->plane.x * cos(-PI/80) - data->raycast->plane.y * sin(-PI/80);
		data->raycast->plane.y = oldPlaneX * sin(-PI/80) + data->raycast->plane.y * cos(-PI/80);
    }
    else if (keycode == 7)
    {
		//both camera direction and camera plane must be rotated
		double oldDirX = data->raycast->dir.x;
		data->raycast->dir.x = data->raycast->dir.x * cos(PI/80) - data->raycast->dir.y * sin(PI/80);
		data->raycast->dir.y = oldDirX * sin(PI/80) + data->raycast->dir.y * cos(PI/80);
		double oldPlaneX = data->raycast->plane.x;
		data->raycast->plane.x = data->raycast->plane.x * cos(PI/80) - data->raycast->plane.y * sin(PI/80);
		data->raycast->plane.y = oldPlaneX * sin(PI/80) + data->raycast->plane.y * cos(PI/80);
    }
	raycasting(data);
	return (0);
}

int **dbltab_copy(int t[24][24], int a, int b)
{
	int **res = malloc(a * sizeof(int *));
	
	for (int i = 0; i < a; i++)
	{
		res[i] = malloc(b * sizeof(int));
		for (int j = 0; j < b; j++)
			res[i][j] = t[i][j];
	}
	return res;
}

int	main(void)
{
	t_data		data[1];
	t_raycast	raycast[1];

//=====================TRUC DEGUEU================================
	t_coord	pos;
	
	data->map_height = 14;
	data->map_width = 33;
	pos.x = 10;
	pos.y = 10;
	
	t_coord	dir;
	t_coord	plane;
	
	dir.x = 1;
	dir.y = 0;
	plane.x = 0;
	plane.y = 0.66;
	
	data->map = parsing("maps/test.cub");
	data->pos = pos;
	raycast->dir = dir;
	raycast->plane = plane;
	raycast->time = 0;
	raycast->oldTime = 0;
	data->raycast = raycast;

//================================================================

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

	data->txtr.nwall.mlx_img = mlx_png_file_to_image(data->mlx, "txtr/north.png", &data->txtr.nwall.width, &data->txtr.nwall.height);
	data->txtr.swall.mlx_img = mlx_png_file_to_image(data->mlx, "txtr/south.png", &data->txtr.swall.width, &data->txtr.swall.height);
	data->txtr.wwall.mlx_img = mlx_png_file_to_image(data->mlx, "txtr/west.png", &data->txtr.wwall.width, &data->txtr.wwall.height);
	data->txtr.ewall.mlx_img = mlx_png_file_to_image(data->mlx, "txtr/east.png", &data->txtr.ewall.width, &data->txtr.ewall.height);

	//mlx_hook(data->win, 2, 1L<<0, ft_close, &data);
	print_background(data);
	raycasting(data);
	mlx_on_event(data->mlx, data->win, 	MLX_KEYDOWN, ft_close, data);
	mlx_loop(data->mlx);
}
