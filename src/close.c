/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 07:43:53 by mbico             #+#    #+#             */
/*   Updated: 2024/12/18 17:12:28 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cube3d.h>

void	close_speaker_text(void	*mlx, t_anim_txtr txt)
{
	uint32_t	i;

	if (!txt.speaker)
		return ;
	i = 0;
	while (i < SPEAKER_FRAME)
	{
		mlx_destroy_image(mlx, txt.speaker[i].img);
		i ++;
	}
	free(txt.speaker);
}

void	close_texture(void *mlx, t_texture *txt)
{
	mlx_destroy_image(mlx, txt[0].img);
	mlx_destroy_image(mlx, txt[1].img);
	mlx_destroy_image(mlx, txt[2].img);
	mlx_destroy_image(mlx, txt[3].img);
	mlx_destroy_image(mlx, txt[4].img);
	mlx_destroy_image(mlx, txt[5].img);
	free(txt);
}

void	close_safe(t_data *data)
{
	int len;

	len = 0;
	close_texture(data->mlx, data->map.txt);
	close_speaker_text(data->mlx, data->map.anim_txtr);
	while (data->screen && len != HEIGHT)
	{
		free(data->screen[len]);
		len++;
	}
	free(data->screen);
	ft_freetab((void *)data->map.content, data->map.size.y);
	ft_freetab((void *)data->psg->ress, INT_MAX);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	exit(EXIT_SUCCESS);
}
