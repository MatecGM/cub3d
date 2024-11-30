/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:49:53 by gadelbes          #+#    #+#             */
/*   Updated: 2024/11/27 20:45:05 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <parsing.h>

int	count_max_x(char **map, int y)
{
	int	count_x;
	int	count_y;
	int	x;

	count_x = 0;
	count_y = tab_size_y(map, y);
	while (count_y != 0)
	{
		x = 0;
		while (map[y][x])
			x++;
		if (count_x < x)
			count_x = x;
		y++;
		count_y--;
	}
	return (count_x);
}
int8_t	**tab_size_x(char **map, int y, int8_t **tab)
{
	int	i;
	int	count_y;

	if (!map)
		return (NULL);
	i = 0;
	count_y = tab_size_y(map, y);
	while (i != count_y + 1)
	{
		tab[i] = ft_calloc(count_max_x(map, y) + 1, sizeof(t_bool));
		if (!tab[i])
		{
			ft_freetab((void *)tab, i);
			return (NULL);
		}
		i++;
	}
	return (tab);
}

int	tab_size_y(char **map, int y)
{
	int	count_y;
	int	x;

	count_y = 0;
	y = find_map(map, 0, 0);
	while (map[y] && map[y][0] != '\n')
	{
		x = 0;
		if (map[y][x] == ' ')
		{
			while (map[y][x] == ' ')
				x++;
			if (map[y][x] == '\n')
				break ;
		}
		count_y++;
		y++;
	}
	return (count_y);
}

int8_t	**tab_map(char **map, int y, int x, int8_t **tab)
{
	int	size_y;
	int	max_x;
	int	i;
	int	j;

	i = 0;
	size_y = tab_size_y(map, y);
	max_x = count_max_x(map, y) - 1;
	while (i < size_y)
	{
		x = 0;
		j = 0;
		while (j < max_x)
		{
			tab[i][j] = find_wall(map, x, y, 1) - 1;
			j++;
			if (map[y][x] != '\0')
				x++;
		}
		tab[i][j] = ERROR;
		i++;
		y++;
	}
	tab[i][0] = ERROR;
	return (tab);
}
