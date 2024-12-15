/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:04:28 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 16:48:44 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_power(double nb, int power)
{
	double	res;

	res = nb;
	while (power > 0)
	{
		res = res * res;
		power --;
	}
	return (res);
}
