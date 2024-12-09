/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:10:07 by mbico             #+#    #+#             */
/*   Updated: 2024/12/09 22:05:25 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSYS_H
# define SSYS_H

# include <pthread.h>
# include <stdint.h>
# include <portaudio.h>
# include <mpg123.h>
# include <libft.h>
# include <pthread.h>

# define MU_PATH "./mu_sfx/Snare.mp3"
# define BUF_SS 64
# define RATE 44100

typedef struct	s_sound
{
	int32_t			channel;
	int32_t			encoding;
	uint8_t			buffer[BUFFER_SIZE];
	long			rate;
	mpg123_handle	*mh;
}	t_sound;

typedef struct s_stream
{
	PaStream	*stream;
	int32_t		channel;
	long		rate;
	t_sound		*sound;
	pthread_t	thread;
	
}	t_stream;

void	ssys_thread_init();

#endif
