/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:25:55 by gadelbes          #+#    #+#             */
/*   Updated: 2024/11/07 22:40:53 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	map_write_check(char **map, int x, int y, int limit)
{
	int	count;

	count = 0;
	while (limit)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != 'N' && map[y][x] != 'S' \
			&& map[y][x] != 'E' && map[y][x] != '1' \
			&& map[y][x] != '0' && map[y][x] != 'W' \
			&& map[y][x] != ' ' && map[y][x] != '\n')
				return (printf("Error\nMap\n"));
			if (map[y][x] == 'N' || map[y][x] == 'S' \
			|| map[y][x] == 'E' || map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
		limit--;
	}
	if (count == 0 || count > 1)
		return (printf("Error\nCharacter\n"));
	return (0);
}

int	verif_wall_bis(char **map, int y, int x, int nb)
{
	while (map[y][x] && map[y][x] != '\n')
	{
		if (map[y][x] != '1' && map[y][x] != ' ')
			return (printf("Error\nMissing Wall\n"));
		x++;
	}
	if (nb == 1)
	{
		y++;
		while (map[y])
		{
			x = 0;
			while (map[y][x])
			{
				if (!ft_is_space(map[y][x]))
					return (printf("Error\nMap Invalid\n"));
				x++;
			}
			y++;
		}
	}
	return (0);
}

int	verif_wall(char **map, int x, int y, int limit)
{
	if (verif_wall_bis(map, y, 0, 0) != 0)
		return (1);
	y++;
	while (limit)
	{
		while (map[y][x])
		{
			if (find_wall(map, 0, y, 1) == 1)
				return (printf("Error\nMissing Wall\n"));
			if (find_wall(map, x, y, 1) == 1)
			{
				if (find_wall(map, x, y + 1, 0) == 0 || \
				find_wall(map, x, y - 1, 0) == 0 || \
				find_wall(map, x - 1, y, 0) == 0 || \
				find_wall(map, x + 1, y, 0) == 0)
					return (printf("Error\nMissing Wall\n"));
			}
			x++;
		}
		x = 0;
		limit--;
		y++;
	}
	return (verif_wall_bis(map, y, 0, 1));
}

int	verif_cub(char *str)
{
	if (ft_strlen(str) <= 4)
		return (printf("Error\n.cub\n"));
	if (ft_strcmp(ft_strrchr(str, '.'), ".cub") != 0)
		return (printf("Error\n.cub\n"));
	return (0);
}

int	verif_data(char **map, int y, char *name)
{
	int	count_data;
	int	x;

	count_data = 0;
	if (verif_cub(name) != 0)
		return (1);
	while (map[y] && count_data != 6)
	{
		x = 0;
		if (ft_is_space(map[y][x]))
		{
			while (map[y][x] == ' ')
				x++;
		}
		if (map[y][x] == '1')
			break ;
		else if (map[y][x] != '\n')
			count_data++;
		y++;
	}
	if (count_data != 6)
		return (printf("Error\nMissing Id\n"));
	if (find_map(map, 0, 0) == 0)
		return (printf("Error\nMissing Map\n"));
	if (count_data != 6)
		return (1);
	if (map_write_check(map, 0, find_map(map, 0, 0), tab_size_y(map, y)) != 0)
		return (1);
	if (verif_wall(map, 0, find_map(map, 0, 0), tab_size_y(map, y) - 2) != 0)
		return (1);
	return (0);
}