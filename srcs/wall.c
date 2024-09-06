/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 01:20:22 by mbico             #+#    #+#             */
/*   Updated: 2024/09/05 16:50:43 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


// int	get_wall_size(t_coord coord, t_coord cam)
// {
// 	double	distance;
// 	double		size;
// 	double		x_power;
// 	double		y_power;

// 	if (ft_absolute(cam.x) > ft_absolute(coord.x))
// 		x_power = ft_power(ft_absolute(cam.x) - (double)ft_absolute(coord.x), 2);
// 	else
// 		x_power = ft_power(ft_absolute(coord.x) - (double)ft_absolute(cam.x), 2);
// 	if (ft_absolute(cam.y) > ft_absolute(coord.y))
// 		y_power = ft_power(ft_absolute(cam.y) - (double)ft_absolute(coord.y), 2);
// 	else
// 		y_power = ft_power(ft_absolute(coord.y) - ft_absolute(cam.y), 2);
// 	distance = sqrt(x_power + y_power);
// 	size = (MESH_HEIGHT / distance);
// 	return (size);
// }

// void	put_wall_col(t_data *data, int x, int size)
// {
// 	int	i;

// 	i = 0;
// 	mlx_pixel_put(data->mlx, data->win, x, HEIGHT / 2 , 0x000000FF);
// 	while(i < size / 2)
// 	{
// 		mlx_pixel_put(data->mlx, data->win, x, HEIGHT / 2 + i , 0x000000FF);
// 		i ++;
// 	}
// 	i = 0;
// 	while(i < size / 2)
// 	{
// 		mlx_pixel_put(data->mlx, data->win, x, HEIGHT / 2 - i , 0x000000FF);
// 		i ++;
// 	}
// }

// t_coord	get_diagonal_direction(int sc_x, int rot)
// {
// 	t_coord	diag;
// 	int		left_rot;
// 	int		x_rot;

// 	left_rot = (rot + 36000 - (FOV_X / 2 * 100) ) % 36000;
// 	x_rot = (int)(sc_x * (FOV_X / (double)WIDTH * 100) + 36000 + left_rot) % 36000;
// 	diag.x = x_rot >= 0 && x_rot < 18000;
// 	diag.y = x_rot >= 9000 && x_rot < 27000;
// 	if (!diag.x)
// 		diag.x = -1;
// 	if (!diag.y)
// 		diag.y = -1;
// 	return (diag);
// }

// t_coord	get_first_square_distance(t_data *data, t_coord diag)
// {
// 	t_coord	wall;

// 	wall.x = fabs(data->cam.x) - floor(fabs(data->cam.x));
// 	wall.y = fabs(data->cam.y) - floor(fabs(data->cam.y));
// 	if (diag.x == 1 && data->cam.x >= 0 || diag.y == -1 && data->cam.x < 0)
// 		wall.x = 1.0 - wall.x;
// 	if (diag.y == 1 && data->cam.y >= 0 || diag.y == -1 && data->cam.y < 0)
// 		wall.y = 1.0 - wall.y;
// 	return (wall);
	
// }

// t_bool	check_wall(t_data *data, t_coord cam, t_coord checker, t_coord diag, int sc_x)
// {
// 	t_coord	real_coord;
	
	
// 	if (checker.x == -1.0 || checker.y == -1.0)
// 		return (FALSE);
// 	real_coord.x = cam.x + (checker.x * diag.x);
// 	real_coord.y = cam.y + (checker.y * diag.y);
// 	if (real_coord.x > data->map_width - 1 || real_coord.x < 0 || real_coord.y > data->map_height - 1 || real_coord.y < 0)
// 		return (FALSE);
// 	if (data->map[(int)round(real_coord.y)][(int)round(real_coord.x)] == 1)
// 		return(TRUE);
// 	return (FALSE);
// }

// t_coord	get_coord_next_wall(t_data *data, int sc_x, int *nb)
// {
// 	t_coord	diag;
// 	double	angle;
// 	int		ray;
// 	t_coord	wall;
// 	t_coord	checker;

// 	diag = get_diagonal_direction(sc_x, data->rot);
// 	angle = ((int)(sc_x * (FOV_X / (double)WIDTH * 100) + 36000 + (data->rot + 36000 - (FOV_X / 2 * 100) ) % 36000) % 9000) / 100.0 * (PI / 180);
// 	ray = 0;
// 	// if (sc_x == 0 || sc_x == WIDTH / 2)
// 	// 	printf("rot %d = %f\n", sc_x, angle);`
// 	wall = get_first_square_distance(data, diag);
// 	checker.x = -1; 
// 	while (ray < RENDER_DISTANCE)
// 	{
// 		if ((diag.x == 1.0 && diag.y == 1.0) || (diag.x == -1.0 && diag.y == -1.0))
// 		{
// 			if (tan(angle) * wall.x + wall.x <= tan(PI / 2 - angle) * wall.y + wall.y)
// 			{
// 				checker.x = wall.x;
// 				checker.y = tan(angle) * wall.x;
// 			}
// 			else
// 			{
// 				checker.y = wall.y;
// 				checker.x = tan(PI / 2.0 - angle) * wall.y;
// 				if (sc_x == WIDTH / 2)
// 					printf("%f\n", tan(PI));
// 			}
// 		}
// 		else
// 		{
// 			if (tan(PI / 2 - angle) * wall.x + wall.x < angle * wall.y + wall.y)
// 			{
// 				checker.x = wall.x;
// 				checker.y = tan(PI / 2 - angle) * wall.x;
// 			}
// 			else
// 			{
// 				checker.y = wall.y;
// 				checker.x = tan(angle) * wall.y;
// 			}
			
// 		}
// 		if (check_wall(data, data->cam, checker, diag, sc_x))
// 		{
// 			checker.x = data->cam.x + (checker.x * diag.x);
// 			checker.y = data->cam.y + (checker.y * diag.y);
// 				//printf("%f %f\n", checker.x, checker.y);
// 			return (checker);
// 		}
// 		ray ++;
// 	}
// 	checker.x = -1;
// 	return (checker);
// }

// void	put_wall(t_data *data)
// {
// 	int		sc_x;
// 	t_coord	coord;
// 	int		size;
// 	int		nb[1];

// 	sc_x = 0;
// 	*nb = 0;
// 	//printf("%f %f dir %d\n", data->cam.x, data->cam.y, data->rot);
// 	while (sc_x < WIDTH)
// 	{
// 		coord = get_coord_next_wall(data, sc_x, nb);
// 		if (coord.x != -1)
// 		{
// 			size = get_wall_size(coord, data->cam);
// 			put_wall_col(data, sc_x, size);
// 		}
// 		sc_x ++;
// 	}
// 	//ft_printf("nb = %d\n", *nb);
// }
