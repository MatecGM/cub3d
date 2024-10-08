/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:34:46 by mbico             #+#    #+#             */
/*   Updated: 2024/10/09 01:44:33 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cube3d.h>

void	display_clear(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_set_image_pixel(data->mlx, data->img, x, y, 0xEEEEEEFF);
			x ++;
		}
		y ++;
	} 
}

void	print_map(t_data *data)
{
	int y;
	int x;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (data->map[y / (HEIGHT / data->map_height)][x / (WIDTH / data->map_width)])
				mlx_set_image_pixel(data->mlx, data->img, x, y, 0xFFFF0000);
			if (y % (HEIGHT / data->map_height) == 0 || x % (WIDTH / data->map_width) == 0)
				mlx_set_image_pixel(data->mlx, data->img, x, y, 0xFF000000);
			x ++;
		}
		y ++;
	}
}

void	print_player(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int j;

	x = data->pos.x * (WIDTH / (double)data->map_width);
	y = data->pos.y * (HEIGHT / (double)data->map_height);
	i = y - 10;
	while (i <= y +10)
	{
		j = x - 10;
		while (j <= x + 10)
		{
			mlx_set_image_pixel(data->mlx, data->img, j, i, 0xFF0000FF);
			j ++;
		}
		i ++;
	}

	t_dcoord	p1;
	t_dcoord	p2;

	p1.x = x;
	p1.y = y;
	p2.x = x + (data->rc.ax) * (WIDTH / (double)data->map_width);
	p2.y = y + (data->rc.ay) * (HEIGHT / (double)data->map_height);
	//print_line(data, p1, p2, 0xFF0000FF);
	int	k = 0;
	while (k < WIDTH)
	{
		double	dir;
		dir = (data->dir - PI / 4.0) + ((PI / 2.0) / (double)WIDTH * k);
		if (dir < 0)
			dir += 2 * PI;
		else if (dir >= PI * 2)
			dir -= 2 * PI;
		t_coord p3 = get_first_wall(data, dir);
		p2.x = p3.x * (WIDTH / (double)data->map_width);
		p2.y = p3.y * (HEIGHT / (double)data->map_height);
		print_line(data, p1, p2, 0xFF000000);
		k ++;
	}
}

void	displaying(t_data *data)
{
	display_clear(data);
	print_map(data);
	print_player(data);
	
}

int	main(void)
{
	t_data		data[1];
	t_coord		pos;

	data->map_height = 15;
	data->map_width = 15;
	pos.x = 6;
	pos.y = 6;
	
	data->map = parsing("maps/test_square.cub");
	data->pos = pos;
	data->dir = PI/2;
//================================================================

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_on_event(data->mlx, data->win, 	MLX_KEYDOWN, ft_keydown, data);
	displaying(data);
	mlx_loop(data->mlx);
}
