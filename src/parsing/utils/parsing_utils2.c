/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:49:10 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 17:15:34 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <parsing.h>

int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	count_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count])
		count++;
	return (count);
}

double	convert_card_to_grad(char card)
{
	if (card == 'S')
		return (PI / 2);
	if (card == 'N')
		return (3 * PI / 2);
	if (card == 'W')
		return (PI);
	return (0);
}

int	verif_map(char **map, int *y)
{
	int	x;
	int	count_data;

	count_data = 0;
	while (map[*y] && count_data != 6)
	{
		x = 0;
		if (ft_is_space(map[*y][x]))
		{
			while (map[*y][x] == ' ')
				x++;
		}
		if (map[*y][x] == '1')
			break ;
		else if (map[*y][x] != '\n')
			count_data ++;
		(*y)++;
	}
	return (count_data);
}

t_bool	color_convert_rgb_hex(uint32_t *color, char *rgb)
{
	char	**split;

	split = ft_split(rgb, ',');
	if (!split)
		return (TRUE);
	*color = 0xFF000000;
	*color |= ft_atoi(split[0]) << 16;
	*color |= ft_atoi(split[1]) << 8;
	*color |= ft_atoi(split[2]);
	ft_freetab((void *)split, 3);
	return (FALSE);
}
