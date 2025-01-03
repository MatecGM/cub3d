/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 01:09:39 by gadelbes          #+#    #+#             */
/*   Updated: 2024/12/18 23:55:51 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <parsing.h>

int	find_wall(char **map, int x, int y, int find_nb)
{
	char	c;

	c = map[y][x];
	if (ft_isdigit(c) || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if ((find_nb == 1 && !ft_isdigit(c)) || c == '0')
			return (1);
		return (c - '0' + 1);
	}
	return (0);
}

int	find_map(char **map, int x, int y)
{
	int	count;

	count = 0;
	while (map[y])
	{
		x = 0;
		while (ft_is_space(map[y][x]) && map[y][x] != '\n')
			x++;
		if (map[y][x] == '1' && count == 6)
			return (y);
		else if (map[y][x] != '\n')
			count++;
		y++;
	}
	return (0);
}
