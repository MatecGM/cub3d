/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssys_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:09:18 by mbico             #+#    #+#             */
/*   Updated: 2024/12/11 17:44:33 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mpg123.h>
#include <ssys.h>	
#include <stdio.h>
#include <cube3d.h>

void	close_lib(uint8_t nb)
{
	const void (*exit_lib[2])(void) = {(void *) Pa_Terminate, (void *)mpg123_exit};
	uint8_t	i;

	i = 0;
	while (i < nb && i < 2)
		exit_lib[i++]();
}

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
	char	*str;

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
		mpg123_getformat(sound.mh, &sound.rate, &sound.channel, &sound.encoding);
	}
	return (sound);
}

PaError	init_stream(t_stream *stream, t_sound *sound, t_data *data)
{
	PaError				err;
	PaStreamParameters	par;

	ft_printf("%u %p\n", *data->hud.mu_code, &data->hud.mumu_code);
	stream->sound = sound;
	stream->mu_code = data->hud.mu_code;
	stream->mumu_code = &data->hud.mumu_code;
	par.device = Pa_GetDefaultOutputDevice();
	par.channelCount = 2;
	par.sampleFormat = paInt16;
    par.suggestedLatency = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->defaultLowOutputLatency;
	par.hostApiSpecificStreamInfo = NULL;
	err = Pa_OpenStream(&stream->stream, NULL, &par,RATE, paFramesPerBufferUnspecified, paClipOff, NULL, NULL);
	Pa_StartStream(stream->stream);
	return (err);
}

void	set_volume(int8_t *samples, size_t sample_count, float volume)
{
	size_t	i;
	int		adjusted_sample;

	i = 0;
	while (i < BUF_SS)
	{
		adjusted_sample = (int32_t)(samples[i] + volume);
		if (adjusted_sample > 32767)
			adjusted_sample = 32767;
		if (adjusted_sample < -32768)
			adjusted_sample = -32768;
		samples[i] = (int8_t)adjusted_sample;
		i ++;
	}
}

void	read_sound_file(t_stream *stream, t_sound *sound, float volume)
{
	size_t		bytes_read;

	while (mpg123_read(sound->mh, sound->buffer, BUF_SS, &bytes_read) == MPG123_OK && mutex_checker(stream->mu_code, stream->mumu_code))
	{
		printf("br %d\n", sound->buffer[0]);
		set_volume(sound->buffer, bytes_read / sizeof(int32_t), volume);
		Pa_WriteStream(stream->stream, sound->buffer, bytes_read / sizeof(int32_t));
	}
}

void	*stream_routine(void *arg)
{
	t_stream	*stream;

	stream = (t_stream *)arg;
	ft_printf("%p %p\n", stream->mu_code, stream->mumu_code);
	while (TRUE)
	{
		if (mutex_checker(stream->mu_code, stream->mumu_code))
		{
			read_sound_file(stream, stream->sound, 0.01);
			mpg123_seek(stream->sound->mh, 0, SEEK_SET);
		}
		usleep(500);
	}
	return NULL;
}

void	ssys_thread_init(void *d)
{
	t_sound		*sound;
	t_stream	*stream;
	t_data		*data;

	data = (t_data *)d;
	sound = ft_calloc(2, sizeof(t_sound));
	stream = ft_calloc(1, sizeof(t_stream));

	ft_printf("%d\n", *data->hud.mu_code);
	if (!sound || init_palib() || init_mpglib() || init_stream(stream, sound, data))
		return ;
	sound[0] = get_sound(MU_PATH);
	if (pthread_create(&stream->thread, NULL, stream_routine, stream))
		return ;
}

