/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:50:22 by mbico             #+#    #+#             */
/*   Updated: 2024/09/06 02:58:45 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


int	get_wall_size(t_raycast *raycast, t_coord coord, t_coord cam)
{
	double	distance;
	double		size;
	double		x_power;
	double		y_power;

	// if (ft_absolute(cam.x) > ft_absolute(coord.x))
	// 	x_power = ft_power(ft_absolute(cam.x) - (double)ft_absolute(coord.x), 2);
	// else
	// 	x_power = ft_power(ft_absolute(coord.x) - (double)ft_absolute(cam.x), 2);
	// if (ft_absolute(cam.y) > ft_absolute(coord.y))
	// 	y_power = ft_power(ft_absolute(cam.y) - (double)ft_absolute(coord.y), 2);
	// else
	// 	y_power = ft_power(ft_absolute(coord.y) - ft_absolute(cam.y), 2);
	// distance = sqrt(x_power + y_power);
	if(raycast->side == 0)
		raycast->perp_wall_dist = (raycast->side_dist.x - raycast->delta_dist.x);
    else
		raycast->perp_wall_dist = (raycast->side_dist.y - raycast->delta_dist.y);
	size = (MESH_HEIGHT / raycast->perp_wall_dist);
	return (size);
}

void	put_wall_col(t_data *data, int x, int size)
{
	int	i;

	int lineHeight = (int)(HEIGHT / data->raycast->perp_wall_dist);

      //calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2.0 + HEIGHT / 2.0;
    if(drawStart < 0.0) drawStart = 0.0;
    int drawEnd = lineHeight / 2.0 + HEIGHT / 2.0;
    if(drawEnd >= HEIGHT) drawEnd = HEIGHT;
	i = drawStart;
	while (i < drawEnd)
	{
		mlx_pixel_put(data->mlx, data->win, x, i , 0x000000FF);
		i ++;
	}
	// mlx_pixel_put(data->mlx, data->win, x, HEIGHT / 2 , 0x000000FF);
	// while(i < size / 2)
	// {
	// 	mlx_pixel_put(data->mlx, data->win, x, HEIGHT / 2 + i , 0x000000FF);
	// 	i ++;
	// }
	// i = 0;
	// while(i < size / 2)
	// {
	// 	mlx_pixel_put(data->mlx, data->win, x, HEIGHT / 2 - i , 0x000000FF);
	// 	i ++;
	// }
}




void	init_step_sidedist(t_data *data, t_raycast *raycast)
{
	if (raycast->ray_dir.x < 0)
	{
		raycast->step.x = -1;
		raycast->side_dist.x = (data->pos.x - raycast->map.x) * raycast->delta_dist.x;
	}
	else
	{
		raycast->step.x = 1;
		raycast->side_dist.x = (raycast->map.x + 1 - data->pos.x) * raycast->delta_dist.x;
	}
	if (raycast->ray_dir.y < 0)
	{
		raycast->step.y = -1;
		raycast->side_dist.y = (data->pos.y - raycast->map.y) * raycast->delta_dist.y;
	}
	else
	{
		raycast->step.y = 1;
		raycast->side_dist.y = (raycast->map.y + 1 - data->pos.y) * raycast->delta_dist.y;
	}
}

void	init_raycasting(t_data *data, t_raycast *raycast)
{
	raycast->map.x = (int)data->pos.x; 
	raycast->map.y = (int)data->pos.y;
	raycast->delta_dist.x = (data->raycast->ray_dir.x == 0) ? 1e30 : fabs(1 / data->raycast->ray_dir.x); 
	raycast->delta_dist.y = (data->raycast->ray_dir.y == 0) ? 1e30 : fabs(1 / data->raycast->ray_dir.y); 
	raycast->hit = FALSE;
	init_step_sidedist(data, raycast);
}

t_coord	dda(t_data *data, t_raycast *raycast)
{
	t_coord	impact;

	while (raycast->hit == FALSE)
	{
		if (raycast->side_dist.x < raycast->side_dist.y)
		{
			raycast->side_dist.x += raycast->delta_dist.x;
			raycast->map.x += raycast->step.x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist.y += raycast->delta_dist.y;
			raycast->map.y += raycast->step.y;
			raycast->side = 1;
		}
		if (raycast->map.x + 1 >= data->map_width || raycast->map.x+ 1 < 0 || raycast->map.y+ 1 >= data->map_height || raycast->map.y+ 1 < 0 || data->map[raycast->map.y+ 1][raycast->map.x+ 1] > 0)
			raycast->hit = TRUE;
	}
	impact.x = (double)raycast->map.x;
	impact.y = (double)raycast->map.y + (1.0 - raycast->step.y) / 2.0;
	return (impact);
}

void	raycasting(t_data *data)
{
	int		sc_x;
	t_coord	camera;
	int		size;
	t_coord	impact;


	sc_x = 0;
	while (sc_x < WIDTH)
	{
		camera.x = 2 * sc_x / (double)(WIDTH);
    	data->raycast->ray_dir.x = data->raycast->dir.x + data->raycast->plane.x * camera.x; 
		data->raycast->ray_dir.y = data->raycast->dir.y + data->raycast->plane.y * camera.x;
		init_raycasting(data, data->raycast);
		impact = dda(data, data->raycast);
		size = get_wall_size(data->raycast, impact, data->pos);
		put_wall_col(data, sc_x, size);
		
		sc_x ++;
	}
	//timing for input and FPS counter
	data->raycast->oldTime = data->raycast->time;
	data->raycast->time = get_time_ms();
	double frameTime = (data->raycast->time - data->raycast->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	//printf("%ffps\n", 1.0 / frameTime);
	//print(1.0 / frameTime); //FPS counter
	//speed modifiers
	data->raycast->moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	data->raycast->rotSpeed = frameTime * 3.0; //the constant value is in radians/second
}
