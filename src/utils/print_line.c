/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:38:32 by mbico             #+#    #+#             */
/*   Updated: 2024/11/17 18:17:39 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	ft_link_point_y(t_data *data, t_dcoord p1, t_dcoord p2, t_argb color)
{
	int		x;
	int		y;
	float	d;
	int		b;

	x = 0;
	y = 0;
	d = (float)(p2.x - p1.x) / (float)(p2.y - p1.y);
	b = (p1.y < p2.y) - (p1.y > p2.y);
	while (y + p1.y != p2.y)
	{
		x = y * d;
		if ((x + p1.x >= 0 && x + p1.x < WIDTH) && (y + p1.y >= 0 && y
				+ p1.y < HEIGHT))
			put_pixel_inscreen(data, p1.x + x, p1.y + y, color);
		y += b;
	}
}

void	print_line(t_data *data, t_dcoord p1, t_dcoord p2, t_argb color)
{
	int		x;
	int		y;
	double	d;
	int		b;

	x = 0;
	y = 0;
	d = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	if (d > 1 || d < -1)
		ft_link_point_y(data, p1, p2, color);
	else
	{
		b = (p1.x < p2.x) - (p1.x > p2.x);
		while (x + p1.x != p2.x)
		{
			y = x * d;
			if ((x + p1.x >= 0 && x + p1.x < WIDTH) && (y + p1.y >= 0 && y
					+ p1.y < HEIGHT))
				put_pixel_inscreen(data, p1.x + x, p1.y + y, color);
			x += b;
		}
	}
}
