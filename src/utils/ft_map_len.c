/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 03:54:33 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 15:31:12 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_dcoord	ft_map_len(int8_t **map)
{
	t_dcoord	size;

	size.y = 0;
	while (map && map[size.y] && map[size.y][0] != ERROR)
		size.y++;
	size.x = 0;
	while (map && map[0] && map[0][size.x])
		size.x++;
	return (size);
}
