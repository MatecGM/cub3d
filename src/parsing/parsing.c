/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:43:00 by mbico             #+#    #+#             */
/*   Updated: 2024/11/08 00:00:07 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	parsing(char *path)
{
	int		y;
	t_bool	**tab;
	char	**id_tab;
	char	**map;

	map = map_parsing(path, 0);
	if (map == NULL)
		return (1);
	if (verif_data(map, 0, path) != 0)
		return (1);
	id_tab = tab_id(map, 0, 0);
	if (!id_tab || !*id_tab)
		return (printf("Error\nMissing Id\n"));
	if (verif_fd(id_tab) != 0)
		return (1);
	if (verif_rgb(id_tab) != 0)
		return (1);
	y = find_map(map, 0, 0);
	char c = find_orentation(map, y); // l'orientation du personnage, fais comme tu veux avec
	tab = ft_calloc(tab_size_y(map, y) + 1, sizeof(t_bool *));
	tab = tab_size_x(map, y, tab);
	tab = tab_map(map, y, 0, tab);
	return (0);
}
