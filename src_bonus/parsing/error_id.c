/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 01:08:13 by gadelbes          #+#    #+#             */
/*   Updated: 2024/12/18 19:20:19 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <parsing.h>

int	fill_id(char *ligne, char **id, t_verif param)
{
	const char	*cardinal[6] = {"NO ", "SO ", "WE ", "EA ", "F ", "C "};
	char		*type;

	type = ft_strdup(cardinal[param]);
	if (type && ft_strncmp(ligne, type, ft_strlen(type)) == 0)
	{
		if (id[param] == NULL)
		{
			ligne += ft_strlen(type) - 1;
			while (ft_without_n(*ligne))
				ligne++;
			id[param] = dup_without_n(ligne);
			free(type);
			return (1);
		}
		free(type);
		return (-1);
	}
	free(type);
	return (0);
}

int	one_ligne(char **id, char *ligne)
{
	int	nb;
	int	result;

	nb = 0;
	while (ft_without_n(*ligne))
		ligne++;
	while (nb != 6)
	{
		result = fill_id(ligne, id, nb);
		if (result == 0)
			nb++;
		else if (result == -1)
		{
			ft_freetab((void **)id, INT_MAX);
			return (-1);
		}
		else
			return (0);
	}
	ft_freetab((void **)id, INT_MAX);
	return (-1);
}

char	**tab_id(char **map, int y, int nb)
{
	int		x;
	char	**id;

	id = ft_calloc(7, sizeof(char *));
	if (!id)
		return (NULL);
	while (nb != 6)
	{
		x = 0;
		while (ft_is_space(map[y][x]))
		{
			if (map[y][x] == '\n')
			{
				y++;
				x = 0;
			}
			else
				x++;
		}
		if (one_ligne(id, map[y]) == -1)
			return (NULL);
		y++;
		nb++;
	}
	return (id);
}

int	number_rgb(char **id_tab, int nb)
{
	int		i;
	char	**split_verif;

	i = 0;
	split_verif = ft_split(id_tab[nb], ',');
	if (!split_verif || !*split_verif || count_tab(split_verif) != 3)
		return (printf("Error\nRGB Format\n"));
	while (split_verif[i])
	{
		if (ft_strlen(split_verif[i]) > 3 || atoi(split_verif[i]) > 255)
		{
			free(split_verif);
			return (printf("Error\nRGB Format\n"));
		}
		i++;
	}
	free(split_verif);
	return (0);
}

int	verif_rgb(char **id_tab)
{
	int	nb;
	int	i;

	nb = 4;
	while (nb != 6)
	{
		i = 0;
		if (count_char(id_tab[nb], ',') != 2)
			return (printf("Error\nRGB Format\n"));
		while (id_tab[nb][i])
		{
			if (isdigit_comma(id_tab[nb][i]) == 0)
				return (printf("Error\nRGB Format\n"));
			i++;
		}
		if (number_rgb(id_tab, nb) != 0)
			return (1);
		nb++;
	}
	return (0);
}
