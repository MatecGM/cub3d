/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_mm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:33:20 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 17:15:18 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coord.h>
#include <cube3d.h>
#include <stdint.h>

void	octant(t_data *data, t_coord center, t_coord ptr, t_argb color)
{
	put_pixel_inscreen(data, center.x + ptr.x, center.y + ptr.y, color);
	put_pixel_inscreen(data, center.x - ptr.x, center.y + ptr.y, color);
	put_pixel_inscreen(data, center.x + ptr.x, center.y - ptr.y, color);
	put_pixel_inscreen(data, center.x - ptr.x, center.y - ptr.y, color);
	put_pixel_inscreen(data, center.x + ptr.y, center.y + ptr.x, color);
	put_pixel_inscreen(data, center.x - ptr.y, center.y + ptr.x, color);
	put_pixel_inscreen(data, center.x + ptr.y, center.y - ptr.x, color);
	put_pixel_inscreen(data, center.x - ptr.y, center.y - ptr.x, color);
}

static t_argb	intensity(t_argb color, double intensity)
{
	t_argb	ret;

	ret.a = 0xFF;
	ret.r = color.r * intensity;
	ret.g = color.g * intensity;
	ret.b = color.b * intensity;
	return (ret);
}

void	circle_mm(t_data *data, t_coord center, uint32_t r, t_argb color)
{
	t_coord		ptr;
	t_coord		ptradd;
	int32_t		m;
	double		delta;

	ptr.x = 0;
	ptr.y = r;
	m = 5 - 4 * r;
	while (ptr.x <= ptr.y)
	{
		delta = ptr.y - (double)floor(ptr.y);
		octant(data, center, ptr, intensity(color, 1 - delta));
		ptradd = ptr;
		ptradd.y += 5;
		octant(data, center, ptradd, intensity(color, 1 - delta));
		if (m > 0)
		{
			ptr.y --;
			m -= 8 * ptr.y;
		}
		ptr.x ++;
		m += 8 * ptr.x + 4;
	}
}
