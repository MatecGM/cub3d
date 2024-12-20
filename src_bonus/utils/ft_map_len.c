/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 03:54:33 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 17:15:59 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_dcoord	ft_map_len(int8_t **map)
{
	t_dcoord	size;

	size.x = 0;
	while (map[0][size.x] != ERROR)
		size.x++;
	size.y = 0;
	while (map[size.y][size.x])
		size.y++;
	return (size);
}
