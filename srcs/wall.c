/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 01:20:22 by mbico             #+#    #+#             */
/*   Updated: 2024/08/29 21:13:20 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


int	get_wall_size(t_coord coord, t_coord cam)
{
	double	distance;
	double		size;
	double		x_power;
	double		y_power;

	if (ft_absolute(cam.x) > ft_absolute(coord.x))
		x_power = ft_power(ft_absolute(cam.x) - (double)ft_absolute(coord.x), 2);
	else
		x_power = ft_power(ft_absolute(coord.x) - (double)ft_absolute(cam.x), 2);
	if (ft_absolute(cam.y) > ft_absolute(coord.y))
		y_power = ft_power(ft_absolute(cam.y) - (double)ft_absolute(coord.y), 2);
	else
		y_power = ft_power(ft_absolute(coord.y) - ft_absolute(cam.y), 2);
	distance = sqrt(x_power + y_power);
	size = (MESH_HEIGHT / distance);
	return (size);
}

void	put_wall_col(t_data *data, int x, int size)
{
	int	i;

	i = 0;
	mlx_pixel_put(data->mlx, data->win, x, HEIGHT / 2 , 0x000000FF);
	while(i < size / 2)
	{
		mlx_pixel_put(data->mlx, data->win, x, HEIGHT / 2 + i , 0x000000FF);
		i ++;
	}
	i = 0;
	while(i < size / 2)
	{
		mlx_pixel_put(data->mlx, data->win, x, HEIGHT / 2 - i , 0x000000FF);
		i ++;
	}
}

t_coord	get_diagonal_direction(int sc_x, int rot)
{
	t_coord	diag;
	int		left_rot;
	int		x_rot;

	left_rot = (rot + 36000 - (FOV_X / 2 * 100) ) % 36000;
	x_rot = (int)(sc_x * (FOV_X / (double)WIDTH * 100) + 36000 + left_rot) % 36000;
	diag.x = x_rot >= 0 && x_rot < 18000;
	diag.y = x_rot >= 9000 && x_rot < 27000;
	if (!diag.x)
		diag.x = -1;
	if (!diag.y)
		diag.y = -1;
	return (diag);

}

t_coord	get_coord_next_wall(t_data *data, int sc_x)
{
	t_coord	diag;
	double	angle;
	int		ray;

	diag = get_diagonal_direction(sc_x, data->rot);
	angle = ((int)(sc_x * (FOV_X / (double)WIDTH * 100) + 36000 + (data->rot + 36000 - (FOV_X / 2 * 100) ) % 36000) % 36000 % 4500) / 100.0 * (PI / 180);
	// if (sc_x == 0 || sc_x == WIDTH / 2)
	// 	printf("rot %d = %f\n", sc_x, angle);
	while (ray < RENDER_DISTANCE)
}

void	put_wall(t_data *data)
{
	int		sc_x;
	t_coord	coord;
	int		size;

	sc_x = 0;
	while (sc_x < WIDTH)
	{
		coord = get_coord_next_wall(data, sc_x);
		// if (coord.x != -1)
		// {
		// 	size = 10;//get_wall_size(coord, cam);
		// 	put_wall_col(data, sc_x, size);
		// }
		sc_x ++;
	}
}
