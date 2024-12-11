/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssys_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:09:18 by mbico             #+#    #+#             */
/*   Updated: 2024/12/11 19:10:37 by yroussea         ###   ########.fr       */
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
	par.suggestedLatency = \
	Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->defaultLowOutputLatency;
	par.hostApiSpecificStreamInfo = NULL;
	err = Pa_OpenStream(&stream->stream, NULL, &par, \
	RATE, paFramesPerBufferUnspecified, paClipOff, NULL, NULL);
	Pa_StartStream(stream->stream);
	return (err);
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
	if (!sound || init_palib() || init_mpglib() \
	|| init_stream(stream, sound, data))
		return ;
	sound[0] = get_sound(MU_PATH);
	if (pthread_create(&stream->thread, NULL, stream_routine, stream))
		return ;
}
