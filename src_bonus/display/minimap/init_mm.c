/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:28:55 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 17:15:20 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

uint32_t	**init_mm(void)
{
	uint32_t	**frame_mm;
	uint8_t		i;

	i = 0;
	frame_mm = ft_calloc(SIZE_MM + 1, sizeof(uint32_t *));
	while (frame_mm && i < SIZE_MM)
	{
		frame_mm[i] = ft_calloc(SIZE_MM + 1, sizeof(uint32_t));
		if (!frame_mm[i])
		{
			ft_freetab((void *)frame_mm, i);
			return (NULL);
		}
		i ++;
	}
	return (frame_mm);
}

void	display_mm_on_screen(t_data *data, uint32_t **frame)
{
	t_dcoord	ptr;

	ptr.y = 0;
	while (ptr.y < 150)
	{
		ptr.x = 0;
		while (ptr.x < 150)
		{
			if (frame[ptr.y][ptr.x] >> 24 != 0)
				put_pixel_inscreen(data, ptr.x + PADDING_MM, \
				ptr.y + PADDING_MM, (t_argb)frame[ptr.y][ptr.x]);
			ptr.x ++;
		}
		ptr.y ++;
	}
}
