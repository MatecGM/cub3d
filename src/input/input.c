/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:46:09 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 17:15:26 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_bool	get_input_state(__uint128_t input, int kc)
{
	return ((input >> kc) & 1);
}

int	keydown(int kc, void *d)
{
	t_data	*data;

	data = (t_data *)d;
	hud_action(data, kc);
	interact_system(data, kc);
	data->input |= ((__uint128_t)1 << kc);
	return (0);
}

int	keyup(int kc, void *d)
{
	t_data	*data;

	data = (t_data *)d;
	data->input &= ~((__uint128_t)1 << kc);
	return (0);
}
