/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_mutiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:01:16 by mbico             #+#    #+#             */
/*   Updated: 2024/08/25 05:04:43 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	round_mutiple(int nb, int mutiple)
{
	if (nb % mutiple < mutiple / 2)
		return (nb - (nb % mutiple));
	else
		return (nb + mutiple - (nb % mutiple));
}
