/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 07:43:53 by mbico             #+#    #+#             */
/*   Updated: 2024/12/18 18:43:47 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cube3d.h>

void	close_texture(void *mlx, t_texture *txt)
{
	mlx_destroy_image(mlx, txt[0].img);
	mlx_destroy_image(mlx, txt[1].img);
	mlx_destroy_image(mlx, txt[2].img);
	mlx_destroy_image(mlx, txt[3].img);
	free(txt);
}

void	close_safe(t_data *data)
{
	int	len;

	len = 0;
	close_texture(data->mlx, data->map.txt);
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
