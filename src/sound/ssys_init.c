/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssys_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:09:18 by mbico             #+#    #+#             */
/*   Updated: 2024/12/09 22:57:56 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mpg123.h>
#include <ssys.h>	

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

PaError	init_stream(t_stream *stream, t_sound *sound)
{
	PaError				err;
	PaStreamParameters	par;

	stream->sound = sound;
	par.device = Pa_GetDefaultOutputDevice();
	par.channelCount = 2;
	par.sampleFormat = paInt16;
    par.suggestedLatency = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->defaultLowOutputLatency;
	par.hostApiSpecificStreamInfo = NULL;
	err = Pa_OpenStream(&stream->stream, NULL, &par,RATE, paFramesPerBufferUnspecified, paClipOff, NULL, NULL);
	Pa_StartStream(stream->stream);
	return (err);
}

void	read_sound_file(t_stream *stream, t_sound *sound)
{
	size_t		bytes_read;

	while (mpg123_read(sound->mh, sound->buffer, BUF_SS, &bytes_read) == MPG123_OK)
        Pa_WriteStream(stream->stream, sound->buffer, bytes_read / sizeof(int32_t));
}

void	*stream_routine(void *arg)
{
	t_stream	*stream;

	stream = (t_stream *)arg;
	read_sound_file(stream, &stream->sound[0]);
	return NULL;
}

void	ssys_thread_init()
{
	t_sound		*sound;
	t_stream	stream;

	sound = ft_calloc(2, sizeof(t_sound));
	if (!sound || init_palib() || init_mpglib() || init_stream(&stream, sound))
		return ;
	sound[0] = get_sound(MU_PATH);
	ft_printf("la = %d / %d\n", sound[0].channel, stream.sound[0].channel);
	sound[0].channel = 0;
	ft_printf("la = %d / %d\n", sound[0].channel, stream.sound[0].channel);
	if (pthread_create(&stream.thread, NULL, stream_routine, &stream))
		return ;
}

