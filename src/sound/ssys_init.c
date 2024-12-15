/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssys_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:09:18 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 17:15:47 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mpg123.h>
#include <ssys.h>	
#include <stdio.h>
#include <cube3d.h>

t_bool	init_palib(void)
{
	PaError	err;

	err = Pa_Initialize();
	if (err)
	{
		ft_printf("PortAudio init error : %s\n", Pa_GetErrorText(err));
		return (TRUE);
	}
	return (FALSE);
}

t_bool	init_mpglib(void)
{
	int32_t	err;

	err = mpg123_init();
	if (err)
	{
		ft_printf("Mpg123 init error : %s\n", mpg123_plain_strerror(err));
		close_lib(1);
		return (TRUE);
	}
	return (FALSE);
}

t_sound	get_sound(char *path)
{
	t_sound			sound;
	int32_t			err;

	sound.mh = mpg123_new(NULL, &err);
	if (sound.mh == NULL)
		ft_printf("Erreur mpg123: %s\n", mpg123_plain_strerror(err));
	else
	{
		mpg123_open(sound.mh, path);
		mpg123_getformat(sound.mh, &sound.rate, &sound.channel, \
		&sound.encoding);
	}
	return (sound);
}

PaError	init_stream(t_stream *stream, t_sound *sound, t_data *data)
{
	PaError				err;
	PaStreamParameters	par;

	ft_printf("%u %p\n", *data->hud.mu_code, &data->hud.mumu_code);
	stream->sound = sound;
	stream->input.mu_code = data->hud.mu_code;
	stream->input.mumu_code = &data->hud.mumu_code;
	stream->input.mu_stereo = data->hud.mu_stereo;
	stream->input.mumu_stereo = &data->hud.mumu_stereo;
	par.device = Pa_GetDefaultOutputDevice();
	par.channelCount = 2;
	par.sampleFormat = paInt16;
	par.suggestedLatency = \
	Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->defaultLowOutputLatency;
	par.hostApiSpecificStreamInfo = NULL;
	err = Pa_OpenStream(&stream->stream, NULL, \
	&par, RATE, paFramesPerBufferUnspecified, paClipOff, NULL, NULL);
	Pa_StartStream(stream->stream);
	return (err);
}

/* void	set_volume(int8_t *samples, float volume) */
/* { */
/* 	size_t	i; */
/* 	int32_t		adjusted_sample; */
/*  */
/* 	i = 0; */
/* 	printf("%d\n", (int)(samples[i] * volume)); */
/* 	while (i < BUF_SS) */
/* 	{ */
/* 		adjusted_sample = (int32_t)(samples[i] * volume); */
/* 		if (adjusted_sample > 32767) */
/* 			adjusted_sample = 32767; */
/* 		if (adjusted_sample < -32768) */
/* 			adjusted_sample = -32768; */
/* 		samples[i] = (int8_t)adjusted_sample; */
/* 		i ++; */
/* 	} */
/* } */

void	ssys_thread_init(void *d)
{
	t_sound		*sound;
	t_stream	*stream;
	t_data		*data;

	data = (t_data *)d;
	sound = ft_calloc(2, sizeof(t_sound));
	stream = ft_calloc(1, sizeof(t_stream));
	if (!sound || init_palib() || init_mpglib() \
		|| init_stream(stream, sound, data))
		return ;
	sound[0] = get_sound(MU_PATH);
	if (pthread_create(&stream->thread, NULL, stream_routine, stream))
		return ;
}
