/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:41:29 by gadelbes          #+#    #+#             */
/*   Updated: 2024/11/20 13:36:30 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

char	**map_parsing_bis(char *map, char *parse_gnl, char **parsed_map)
{
	int	nb;
	int	fd;

	if (!parsed_map)
		return (NULL);
	nb = 0;
	fd = open(map, O_RDONLY);
	parse_gnl = get_next_line(fd);
	while (parse_gnl)
	{
		parsed_map[nb] = ft_strdup(parse_gnl);
		free(parse_gnl);
		parse_gnl = get_next_line(fd);
		nb++;
	}
	close(fd);
	return (parsed_map);
}

char	**map_parsing(char *map, int nb)
{
	int		fd;
	char	*parse_gnl;
	char	**parsed_map;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (NULL);
	parse_gnl = get_next_line(fd);
	while (parse_gnl)
	{
		free(parse_gnl);
		parse_gnl = get_next_line(fd);
		nb++;
	}
	close(fd);
	parsed_map = ft_calloc(nb + 1, sizeof(char *));
	return (map_parsing_bis(map, parse_gnl, parsed_map));
}

int	verif_fd(char **id_tab)
{
	int	fd;
	int	nb;

	nb = 0;
	fd = -1;
	while (nb != 4)
	{
		if (verif_png(id_tab[nb]) != 0)
			return (1);
		fd = open(id_tab[nb], O_RDONLY, 644);
		if (fd < 0)
			return (printf("Error\nOpen Texture\n"));
		close(fd);
		fd = -1;
		nb++;
	}
	return (0);
}

int	verif_png(char *str)
{
	if (ft_strlen(str) <= 4)
		return (printf("Error\n.png\n"));
	if (ft_strcmp(ft_strrchr(str, '.'), ".png") != 0)
		return (printf("Error\n.png\n"));
	return (0);
}

char	find_orentation(char **map, int y, t_coord *pos)
{
	int	x;
	int	rel_y;

	rel_y = y;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				pos->x = (double)x + 0.5;
				pos->y = (double)y + 0.5 - (double)rel_y;
				return (map[y][x]);
			}
			x++;
		}
		y++;
	}
	return (0);
}
