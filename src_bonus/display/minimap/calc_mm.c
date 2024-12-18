/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_mm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:39:46 by mbico             #+#    #+#             */
/*   Updated: 2024/12/11 18:36:33 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <stdint.h>

t_bool	circle_calc(int32_t x, int32_t y)
{
	uint32_t	dist;

	dist = pow(x - 75, 2) + pow(y - 75, 2);
	if (dist <= 5625)
		return (TRUE);
	return (FALSE);
}

t_bool	put_pixel_on_mm(
uint32_t **frame_mm, int32_t x,
int32_t y, uint32_t color)
{
	if (x >= 0 && x < SIZE_MM && y >= 0 && y < SIZE_MM && circle_calc(x, y))
	{
		frame_mm[y][x] = color;
		return (TRUE);
	}
	return (FALSE);
}
