/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:50:22 by mbico             #+#    #+#             */
/*   Updated: 2024/09/20 08:47:09 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_wall_size(t_raycast *raycast, t_coord coord, t_coord cam)
{
	double	distance;
	double	size;
	double	x_power;
	double	y_power;

	if (raycast->side == 0)
		raycast->perp_wall_dist = (raycast->side_dist.x
				- raycast->delta_dist.x);
	else
		raycast->perp_wall_dist = (raycast->side_dist.y
				- raycast->delta_dist.y);
	size = (MESH_HEIGHT / raycast->perp_wall_dist);
	return (size);
}

void	put_wall_col(t_data *data, int x, int size)
{
	int	i;
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HEIGHT / data->raycast->perp_wall_dist);
	draw_start = -line_height / 2.0 + HEIGHT / 2.0;
	if (draw_start < 0.0)
		draw_start = 0.0;
	draw_end = line_height / 2.0 + HEIGHT / 2.0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT;
	i = draw_start;
	while (i < draw_end)
	{
		mlx_set_image_pixel(data->mlx, data->img, x, i, 0xFF0000FF);
		//mlx_pixel_put(data->mlx, data->win, x, i, 0x000000FF);
		i++;
	}
}

void	init_step_sidedist(t_data *data, t_raycast *raycast)
{
	if (raycast->ray_dir.x < 0)
	{
		raycast->step.x = -1;
		raycast->side_dist.x = (data->pos.x - raycast->map.x)
			* raycast->delta_dist.x;
	}
	else
	{
		raycast->step.x = 1;
		raycast->side_dist.x = (raycast->map.x + 1 - data->pos.x)
			* raycast->delta_dist.x;
	}
	if (raycast->ray_dir.y < 0)
	{
		raycast->step.y = -1;
		raycast->side_dist.y = (data->pos.y - raycast->map.y)
			* raycast->delta_dist.y;
	}
	else
	{
		raycast->step.y = 1;
		raycast->side_dist.y = (raycast->map.y + 1 - data->pos.y)
			* raycast->delta_dist.y;
	}
}

void	init_raycasting(t_data *data, t_raycast *raycast)
{
	raycast->map.x = (int)data->pos.x;
	raycast->map.y = (int)data->pos.y;
	if (data->raycast->ray_dir.x == 0)
		raycast->delta_dist.x = 1e30;
	else
		raycast->delta_dist.x = fabs(1 / data->raycast->ray_dir.x);
	if (data->raycast->ray_dir.y == 0)
		raycast->delta_dist.y = 1e30;
	else
		raycast->delta_dist.y = fabs(1 / data->raycast->ray_dir.y);
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
		if (raycast->map.x + 1 >= data->map_width || raycast->map.x + 1 < 0
			|| raycast->map.y + 1 >= data->map_height || raycast->map.y + 1 < 0
			|| data->map[raycast->map.y + 1][raycast->map.x + 1] > 0)
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
		data->raycast->ray_dir.x = data->raycast->dir.x + data->raycast->plane.x
			* camera.x;
		data->raycast->ray_dir.y = data->raycast->dir.y + data->raycast->plane.y
			* camera.x;
		init_raycasting(data, data->raycast);
		impact = dda(data, data->raycast);
		size = get_wall_size(data->raycast, impact, data->pos);
		put_wall_col(data, sc_x, size);
		sc_x++;
	}
}
