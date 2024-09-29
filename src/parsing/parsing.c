/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:41:29 by gadelbes          #+#    #+#             */
/*   Updated: 2024/09/20 07:24:52 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

char	**map_parsing(char *map, int nb, int fd)
{
	char	*parse_gnl;
	char	**parsed_map;

	if (fd == -1)
		return (NULL);
	parse_gnl = get_next_line(fd);
	while(parse_gnl)
	{
		free(parse_gnl);
		parse_gnl = get_next_line(fd);
		nb++;
	}
	close(fd);
	parsed_map = ft_calloc(nb + 1, sizeof(char *));
	nb = 0;
	fd = open(map, O_RDONLY);
	parse_gnl = get_next_line(fd);
	while(parse_gnl)
	{
		parsed_map[nb] = ft_strdup(parse_gnl);
		free(parse_gnl);
		parse_gnl = get_next_line(fd);
		nb++;
	}
	close(fd);
	return (parsed_map);
}

t_bool	**parsing(char *path)
{
	int		y;
	t_bool	**tab;
	char	**map;
	int		max_y;

	map = map_parsing(path, 0, open(path, O_RDONLY));
	if (map == NULL || verif_data(map, 0) != 0)
		return (NULL);
	y = find_map(map, 0, 0);
	max_y = tab_size_y(map, y, 0);
	tab = ft_calloc(tab_size_y(map, y, 0) + 1, sizeof(t_bool *));
	if (!tab)
		return (NULL);
	tab = tab_size_x(map, y, tab);
	if (!tab)
		return (NULL);
	tab = tab_map(map, y, 0, tab);
	ft_freetab((void **)map, max_y);
	return (tab);
}


	// printf("good\n");
