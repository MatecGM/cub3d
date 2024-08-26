/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 01:20:22 by mbico             #+#    #+#             */
/*   Updated: 2024/08/25 14:41:37 by mbico            ###   ########.fr       */
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

t_coord	get_first_wall(t_coord *wall, double x, double y)
{
	int	i;
	
	i = 0;
	while (wall[i].x != -1)
	{
		if (wall[i].x == x && wall[i].y == y)
			return (wall[i]);
		i ++;
	}
	return (wall[i]);
}

t_coord	get_precise_wall_collide(t_coord cam, t_coord gwall, double c)
{
	t_coord		res;
	
	res.x = gwall.x - 50
	
	return (res);
}

t_coord	get_coord_next_wall(t_coord *wall, t_coord cam, int x)
{
	double	c;
	int	ray;
	t_coord	coord;
	t_coord	tmp;

	c = (2 / (double)WIDTH) * (x + 1) - 1;
	ray = 0;
	while (ray < RENDER_DISTANCE)
	{
		tmp = get_first_wall(wall, (int)(ray + cam.x), (int)(ray * c + cam.y));
		if (tmp.x != -1)
		{
			return (coord);
		}
		ray ++;
	}
	return (tmp);
}

void	put_wall(t_data *data, t_coord *wall, t_coord cam)
{
	int		x;
	t_coord	coord;
	int		size;

	x = 0;
	while (x < WIDTH)
	{
		coord = get_coord_next_wall(wall, cam, x);
		if (coord.x != -1)
		{
			size = get_wall_size(coord, cam);
			put_wall_col(data, x, size);
		}
		x ++;
	}
}
