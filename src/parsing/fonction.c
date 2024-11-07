/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 01:09:39 by gadelbes          #+#    #+#             */
/*   Updated: 2024/11/07 22:40:47 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	find_wall(char **map, int x, int y, int find_nb)
{
	char	c;

	c = map[y][x];
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (find_nb == 1 && c != '1')
			return (1);
		return (2);
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
		if (map[y][x] == '1' && count >= 6)
			return (y);
		else if (map[y][x] != '\n')
			count++;
		y++;
	}
	return (0);
}
