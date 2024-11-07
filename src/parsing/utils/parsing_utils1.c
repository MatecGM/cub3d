/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:47:27 by mbico             #+#    #+#             */
/*   Updated: 2024/11/07 23:49:22 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int    ft_without_n(char c)
{
    if (c == ' ' || c == 9 || (c >= 11 && c <= 13))
        return (1);
    return (0);
}

char    *dup_without_n(const char *src)
{
    int        size;
    char    *dest;

    size = 0;
    dest = ft_calloc(sizeof(char), (ft_strlen(src) + 1));
    if (dest == NULL)
        return (NULL);
    while (!ft_is_space(src[size]))
    {
        dest[size] = src[size];
        size++;
    }
    dest[size] = '\0';
    return (dest);
}

int    ft_is_space(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

int    isdigit_comma(int i)
{
    if ((i >= '0' && i <= '9') || i == ',')
        return (1);
    return (0);
}
