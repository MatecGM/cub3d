/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:10:07 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 16:47:48 by gadelbes         ###   ########.fr       */
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
# include <coord.h>

# define MU_PATH "./mu_sfx/Polyphia_Playing_God.mp3"
# define BUF_SS 64
# define RATE 44100

typedef struct s_sound
{
	int32_t			channel;
	int32_t			encoding;
	int16_t			buffer[BUF_SS];
	long			rate;
	mpg123_handle	*mh;
}	t_sound;

typedef struct s_input_ss
{
	uint8_t			*mu_code;
	pthread_mutex_t	*mumu_code;
	t_coord			*mu_stereo;
	pthread_mutex_t	*mumu_stereo;
}	t_input_ss;

typedef struct s_stream
{
	PaStream		*stream;
	int32_t			channel;
	long			rate;
	t_sound			*sound;
	pthread_t		thread;
	t_input_ss		input;
}	t_stream;

void	ssys_thread_init(void *d);
void	close_lib(uint8_t nb);
void	*stream_routine(void *arg);

#endif
