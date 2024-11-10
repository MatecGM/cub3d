/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:49:10 by mbico             #+#    #+#             */
/*   Updated: 2024/11/10 04:56:13 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int    count_char(char *str, char c)
{
    int    i;
    int    count;

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

int    count_tab(char **tab)
{
    int    count;

    count = 0;
    while (tab[count])
        count++;
    return (count);
}

double  convert_card_to_grad(char card)
{
    if (card == 'S')
        return (PI / 2);
    if (card == 'N')
        return (3 * PI / 2);
    if (card == 'W')
        return (PI);
    return (0);
}