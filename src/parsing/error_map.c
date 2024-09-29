/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:25:55 by gadelbes          #+#    #+#             */
/*   Updated: 2024/09/20 07:24:49 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

int	map_write_check(char **map, int x, int y)
{
	int	count;

	count = 0;
	while (map[y][0] == '\n')
		y++;
	while (map[y])
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
	}
	if (count == 0 || count > 1)
		return (printf("Error\nCharacter\n"));
	return (0);
}

int find_wall(char **map, int x, int y, int find_nb)
{
	char	c;

	c = map[y][x];
	if (c == '0'|| c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (find_nb == 1 && c != '1')
			return (1);
		return (2);
	}
	return (0);	
}

int verif_wall(char **map, int x, int y)
{
	while (map[y][0] == '\n')
		y++;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
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
		y++;
	}
	return (0);
}

// int	verif_id(char **map, int x, int y)
// {
// 	char **texture;
// 	int	stop;
// 	int test = 0;

// 	stop = find_map(map, 0, 0);
// 	texture = ft_calloc(11, sizeof(char *));
// 	while(y != stop)
// 	{
// 		x = 0;
// 		if(map[y][0] == '\n')
// 			y++;
// 		while(ft_is_space(map[y][x]))
// 			x++;
// 		if (x < (int)ft_strlen(map[y]))
// 		{
// 			x += 2;
// 			while(ft_is_space(map[y][x]))
// 				x++;
// 			texture[test] = ft_strdup(map[y] + x);
// 			test++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }

int verif_nb_id(char **map, int x, int y, int nb)
{
	int count = 0;

	while(map[y][0] == '\n')
		y++;
	while(ft_isspace(map[y][x]))
		x++;
	while(map[y][x] != ' ' && x < (int)ft_strlen(map[y]))
	{
		count++;
		x++;
	}
	if (count > 2)
		return (printf("Error\nTexture ID\n"));
	if (nb != 5)
		return (verif_nb_id(map, 0, y + 1, nb + 1));
	return (0);
}

int	verif_data(char **map, int y)
{
	int count_data;
	int x;

	count_data = 0;
	while(map[y] && count_data != 6)
	{
		x = 0;
		if (ft_isspace(map[y][x]))
		{
			while (map[y][x] == ' ')
				x++;
		}
		if (map[y][x] == '1')
			break;
		else if (map[y][x] != '\n')
			count_data++;
		y++;
	}
	if (count_data != 6)
		return (1);
	if (verif_nb_id(map, 0, 0, 0) != 0)
		return (1);
	// if (verif_id(map, 0, 0) != 0)
	// 	return (printf("pasbon\n"));// pas fini
	if (map_write_check(map, 0, y) != 0)
		return (1);
	if (verif_wall(map, 0, y) != 0)
		return (1);
	return (0);
}
