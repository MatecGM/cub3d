/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:19:58 by mbico             #+#    #+#             */
/*   Updated: 2024/10/30 19:58:34 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	display_map_mm(t_data *data)
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

void	display_viewray(t_data *data, t_dcoord rel_pos)
{
	t_coord		hit;
	t_dcoord	rel_hit;
	int			i;
	double		dir;

	i = 0;
	while (i < WIDTH)
	{
		dir = (data->dir - PI / 4.0) + ((PI / 2.0) / (double)WIDTH * i);
		if (dir < 0)
			dir += 2 * PI;
		else if (dir >= PI * 2)
			dir -= 2 * PI;
		hit = get_first_wall(data, dir);
		rel_hit.x = hit.x * (WIDTH / (double)data->map_width) - 1;
		rel_hit.y = hit.y * (HEIGHT / (double)data->map_height);
		print_line(data, rel_pos, rel_hit, 0xFF6666FF);
		i ++;
	}
}

void	display_player_mm(t_data *data)
{
	t_dcoord	rel_pos;
	t_dcoord	ptr;

	rel_pos.x = data->pos.x * (WIDTH / (double)data->map_width);
	rel_pos.y = data->pos.y * (HEIGHT / (double)data->map_height);
	ptr.y = rel_pos.y - 10;
	while (ptr.y <= rel_pos.y +10)
	{
		ptr.x = rel_pos.x - 10;
		while (ptr.x <= rel_pos.x + 10)
		{
			mlx_set_image_pixel(data->mlx, data->img, ptr.x, ptr.y, 0xFF0000FF);
			ptr.x ++;
		}
		ptr.y ++;
	}
	display_viewray(data, rel_pos);
}
