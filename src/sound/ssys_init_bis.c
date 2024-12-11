/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssys_init_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:44:18 by gadelbes          #+#    #+#             */
/*   Updated: 2024/12/11 18:48:39 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mpg123.h>
#include <ssys.h>	
#include <stdio.h>
#include <cube3d.h>

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
	return (NULL);
}

void	read_sound_file(t_stream *stream, t_sound *sound, float volume)
{
	size_t		bytes_read;

	while (mpg123_read(sound->mh, sound->buffer, \
	BUF_SS, &bytes_read) == MPG123_OK && \
	mutex_checker(stream->mu_code, stream->mumu_code))
	{
		printf("br %d\n", sound->buffer[0]);
		set_volume(sound->buffer, bytes_read / sizeof(int32_t), volume);
		Pa_WriteStream(stream->stream, sound->buffer, \
		bytes_read / sizeof(int32_t));
	}
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
		mpg123_getformat(sound.mh, &sound.rate, \
		&sound.channel, &sound.encoding);
	}
	return (sound);
}
