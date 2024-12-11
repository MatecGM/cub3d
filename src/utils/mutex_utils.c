/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:41:09 by mbico             #+#    #+#             */
/*   Updated: 2024/12/10 22:58:40 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <pthread.h>

uint8_t	mutex_checker(uint8_t *nb, pthread_mutex_t *mutex)
{
	uint8_t	value;

	pthread_mutex_lock(mutex);
	value = *nb;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	mutex_set_int(uint8_t *var, uint8_t new, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = new;
	pthread_mutex_unlock(mutex);
}

