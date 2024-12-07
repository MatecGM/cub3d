/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:43:00 by mbico             #+#    #+#             */
/*   Updated: 2024/11/27 22:28:58 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <parsing.h>

t_bool	parsing(char *path, t_parse *psg)
{
	int		y;
	char	**map;

	map = map_parsing(path, 0);
	if (!map || verif_data(map, 0, path))
		return (TRUE);
	psg->ress = tab_id(map, 0, 0);
	if (!psg->ress || !*psg->ress)
		return (TRUE);
	if (verif_fd(psg->ress) || verif_rgb(psg->ress))
		return (TRUE);
	y = find_map(map, 0, 0);
	psg->card = find_orentation(map, y, &psg->pos);
	psg->map = ft_calloc(tab_size_y(map, y) + 1, sizeof(t_bool *));
	psg->map = tab_size_x(map, y, psg->map);
	if (!psg->map)
		return (TRUE);
	psg->map = tab_map(map, y, 0, psg->map);
	ft_freetab((void *)map, INT_MAX);
	return (FALSE);
}
