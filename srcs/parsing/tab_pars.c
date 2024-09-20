/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:49:53 by gadelbes          #+#    #+#             */
/*   Updated: 2024/09/20 07:39:53 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	count_max_x(char **map, int y)
{
	int	count_x;
	int count_y;
	int	x;

	count_x = 0;
	count_y = tab_size_y(map, y, 0);
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
	return  (count_x);
}

t_bool	**tab_size_x(char **map, int y, t_bool **tab)
{
	int	i;
	int count_y;

	i = 0;
	count_y = tab_size_y(map, y, 0);
	while (i != count_y + 1)
	{
		tab[i] = ft_calloc(count_max_x(map, y) + 1, sizeof(t_bool));
		i++;
	}
	return (tab);
}

int	tab_size_y(char **map, int y, int x)
{
	int	count_y;

	count_y = 0;
	while (map[y])
	{
		x = 0;
		if (map[y][0] != '\n')
		{
			while (map[y][x] == ' ')
				x++;
			if (map[y][x] != '\n')
				count_y++;
		}
		y++;
	}
	return (count_y);
}

int	find_map(char **map, int x, int y)
{
	int	count;

	count = 0;
	while (map[y] && count != 6)
	{
		x = 0;
		while (ft_isspace(map[y][x]) && map[y][x] != '\n')
			x++;
		if (map[y][x] == '1')
			break ;
		else if (map[y][x] != '\n')
			count++;
		y++;
	}
	return (y);
}

t_bool	**tab_map(char **map, int y, int x, t_bool **tab)
{
	int	nb;
	int nbb;
	int	i;
	int	j;

	i = 0;
	nb = tab_size_y(map, y, x);
	nbb = count_max_x(map, y) - 1;
	while (i != nb)
	{
		x = 0;
		j = 0;
		while (j < nbb)
		{
			tab[i][j] = find_wall(map, x, y, 1) != 1;
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
