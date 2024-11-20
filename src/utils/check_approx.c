/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_approx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:21:17 by mbico             #+#    #+#             */
/*   Updated: 2024/11/17 04:52:57 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_bool	check_approx(double nb1, double nb2, int approx)
{
	if (floor(nb1 * approx) == floor(nb2 * approx))
		return (TRUE);
	return (FALSE);
}
