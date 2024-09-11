/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:22:45 by mbico             #+#    #+#             */
/*   Updated: 2024/09/11 19:30:09 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_close(int keycode, t_data *data)
{
	print_background(data);
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 114)
	{
		data->pos.x = 1;
		data->pos.y = 1;
	}
	if (keycode == 119)
    {
		data->pos.x += data->raycast->dir.x + data->raycast->plane.x;
		data->pos.y += data->raycast->dir.y + data->raycast->plane.y;
    }
    //move backwards if no wall behind you
    if (keycode == 115)
    {
		data->pos.x -= data->raycast->dir.x + data->raycast->plane.x;
		data->pos.y -= data->raycast->dir.y + data->raycast->plane.y;                                                              
    }
	if (keycode == 97)
    {
      //both camera direction and camera plane must be rotated
		double oldDirX = data->raycast->dir.x;
		data->raycast->dir.x = data->raycast->dir.x * cos(-PI/80) - data->raycast->dir.y * sin(-PI/80);
		data->raycast->dir.y = oldDirX * sin(-PI/80) + data->raycast->dir.y * cos(-PI/80);
		double oldPlaneX = data->raycast->plane.x;
		data->raycast->plane.x = data->raycast->plane.x * cos(-PI/80) - data->raycast->plane.y * sin(-PI/80);
		data->raycast->plane.y = oldPlaneX * sin(-PI/80) + data->raycast->plane.y * cos(-PI/80);
    }
    //rotate to the left
    else if (keycode == 100)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = data->raycast->dir.x;
      data->raycast->dir.x = data->raycast->dir.x * cos(PI/80) - data->raycast->dir.y * sin(PI/80);
      data->raycast->dir.y = oldDirX * sin(PI/80) + data->raycast->dir.y * cos(PI/80);
      double oldPlaneX = data->raycast->plane.x;
      data->raycast->plane.x = data->raycast->plane.x * cos(PI/80) - data->raycast->plane.y * sin(PI/80);
      data->raycast->plane.y = oldPlaneX * sin(PI/80) + data->raycast->plane.y * cos(PI/80);
    }
	printf("plane : %f %f\n", data->raycast->plane.x, data->raycast->plane.y);
	printf("dir : %f %f\n\n", data->raycast->dir.x, data->raycast->dir.y);
	raycasting(data);
	return (0);
}

int	ft_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	raycasting(data);
	sleep(0);
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
	int	map[24][24] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	t_coord	pos;
	
	data->map_height = 24;
	data->map_width = 24;
	pos.x = 1;
	pos.y = 1;
	
	t_coord	dir;
	t_coord	plane;
	
	dir.x = 1;
	dir.y = 0;
	plane.x = 0;
	plane.y = 0.66;
	
	data->map = dbltab_copy(map, 24, 24);
	data->pos = pos;
	raycast->dir = dir;
	raycast->plane = plane;
	raycast->time = 0;
	raycast->oldTime = 0;
	data->raycast = raycast;
	
//================================================================

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	print_background(data);
	mlx_hook(data->win, 2, 1L<<0, ft_close, &data);
	raycasting(data);
	//mlx_loop_hook(data->mlx, &ft_loop, data);
	mlx_loop(data->mlx);
}
