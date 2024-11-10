/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:58:31 by mbico             #+#    #+#             */
/*   Updated: 2024/11/10 21:46:27 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int32_t	**init_screen(void)
{
	int32_t		**screen;
	uint32_t	y;

	y = 0;
	screen = ft_calloc(HEIGHT, sizeof(int32_t *));
	if (!screen)
		return (NULL);
	while (y < HEIGHT)
	{
		screen[y] = ft_calloc(WIDTH, sizeof(int32_t));
		if (!screen[y])
		{
			ft_freetab((void **)screen, y);
			return (NULL);
		}
		y ++;
	}
	return (screen);
}
