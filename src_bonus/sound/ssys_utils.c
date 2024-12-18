/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:35:15 by gadelbes          #+#    #+#             */
/*   Updated: 2024/12/15 18:45:47 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mpg123.h>
#include <ssys.h>	
#include <stdio.h>
#include <cube3d.h>

void	close_lib(uint8_t nb)
{
	uint8_t		i;
	static void	(*exit_lib[2])(void) = \
		{(void *) Pa_Terminate, (void *)mpg123_exit};

	i = 0;
	while (i < nb && i < 2)
		exit_lib[i++]();
}

void	apply_volume_per_channel(int16_t *samples,
double left_volume, double right_volume)
{
	size_t	i;

	i = 0;
	while (i < BUF_SS / 2)
	{
		samples[2 * i] = (short)(samples[2 * i] * left_volume);
		samples[2 * i + 1] = (short)(samples[2 * i + 1] * right_volume);
		i ++;
	}
}

void	read_sound_file(t_stream *stream, t_sound *sound)
{
	size_t		bytes_read;
	t_coord		vol;

	while (mpg123_read(sound->mh, sound->buffer, \
		BUF_SS, &bytes_read) == MPG123_OK)
	{
		if (mutex_checker(stream->input.mu_code, stream->input.mumu_code))
		{
			vol = mutex_checker_coord(stream->input.mu_stereo, \
				stream->input.mumu_stereo);
			if (vol.x > 1)
				vol.x = 1.;
			if (vol.y > 1)
				vol.y = 1.;
			apply_volume_per_channel(sound->buffer, vol.x, vol.y);
			Pa_WriteStream(stream->stream, sound->buffer, \
				bytes_read / sizeof(int32_t));
		}
	}
}

void	*stream_routine(void *arg)
{
	t_stream	*stream;

	stream = (t_stream *)arg;
	while (TRUE)
	{
		if (mutex_checker(stream->input.mu_code, stream->input.mumu_code))
		{
			read_sound_file(stream, stream->sound);
		}
		mpg123_seek(stream->sound->mh, 0, SEEK_SET);
		usleep(500);
	}
	return (NULL);
}
