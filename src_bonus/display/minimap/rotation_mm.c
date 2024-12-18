/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_mm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:15:28 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 17:15:20 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <limits.h>

uint32_t	**rotate_mm(uint32_t **src, double dir)
{
	uint32_t	**dst;
	t_dcoord	ptr;
	t_dcoord	ptrm;

	dst = init_mm();
	ptr.y = 0;
	dir = -dir + 3 * PI / 2.;
	while (ptr.y < SIZE_MM)
	{
		ptr.x = 0;
		while (ptr.x < SIZE_MM)
		{
			ptrm.x = (int)(75 + (ptr.x - 75) * cos(dir) + \
			(ptr.y - 75) * sin(dir));
			ptrm.y = (int)(75 - (ptr.x - 75) * sin(dir) + \
			(ptr.y - 75) * cos(dir));
			if (ptrm.x >= 0 && ptrm.x < SIZE_MM && \
			ptrm.y >= 0 && ptrm.y < SIZE_MM)
				dst[ptr.y][ptr.x] = src[ptrm.y][ptrm.x];
			ptr.x ++;
		}
		ptr.y ++;
	}
	ft_freetab((void *)src, SIZE_MM);
	return (dst);
}
