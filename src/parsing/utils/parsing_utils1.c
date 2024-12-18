/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:47:27 by mbico             #+#    #+#             */
/*   Updated: 2024/12/18 21:03:06 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	ft_without_n(char c)
{
	if (c == ' ' || c == 9 || (c >= 11 && c <= 13))
		return (1);
	return (0);
}

char	*dup_without_n(const char *src)
{
	int		size;
	int		size_two;
	char	*dest;

	size = 0;
	size_two = 0;
	dest = ft_calloc(sizeof(char), (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[size_two] != '\n')
	{
		dest[size] = src[size_two];
		if (ft_is_space(src[size_two]))
			size_two++;
		else
		{
			size++;
			size_two++;
		}
	}
	dest[size] = '\0';
	return (dest);
}

int	ft_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	isdigit_comma(int i)
{
	if ((i >= '0' && i <= '9') || i == ',')
		return (1);
	return (0);
}
