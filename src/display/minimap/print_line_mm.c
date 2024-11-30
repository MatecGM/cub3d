/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line_mm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:38:32 by mbico             #+#    #+#             */
/*   Updated: 2024/11/20 16:03:58 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

static void	ft_link_point_y(uint32_t **frame, t_dcoord p1, t_dcoord p2, t_argb color)
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
		{
			if (!put_pixel_on_mm(frame, p1.x + x, p1.y + y, color.argb))
				break;
		}
		y += b;
	}
}

void	print_line_mm(uint32_t **frame, t_dcoord p1, t_dcoord p2, t_argb color)
{
	int		x;
	int		y;
	double	d;
	int		b;

	x = 0;
	y = 0;
	d = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	if (d > 1 || d < -1)
		ft_link_point_y(frame, p1, p2, color);
	else
	{
		b = (p1.x < p2.x) - (p1.x > p2.x);
		while (x + p1.x != p2.x)
		{
			y = x * d;
			if ((x + p1.x >= 0 && x + p1.x < WIDTH) && (y + p1.y >= 0 && y
					+ p1.y < HEIGHT))
			{
				if (!put_pixel_on_mm(frame, p1.x + x, p1.y + y, color.argb))
					break;
			}
			x += b;
		}
	}
}
