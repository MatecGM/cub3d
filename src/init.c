/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 04:58:43 by mbico             #+#    #+#             */
/*   Updated: 2024/12/12 20:43:22 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cube3d.h>
#include <pthread.h>

int32_t	**init_screen(void)
{
	int32_t		**screen;
	uint32_t	y;

	y = 0;
	screen = ft_calloc(HEIGHT, sizeof(int32_t *));
	if (!screen)
		return (NULL);
	while (y < HEIGHT)
	{
		screen[y] = ft_calloc(WIDTH, sizeof(int32_t));
		if (!screen[y])
		{
			ft_freetab((void **)screen, y);
			return (NULL);
		}
		y++;
	}
	return (screen);
}



t_bool	init_anim_txtr(t_data *data, t_anim_txtr	*txtr)
{
	uint8_t	i;
	char	*path;

	txtr->speaker = ft_calloc(SPEAKER_FRAME + 1, sizeof(t_texture));
	if (!txtr->speaker)
		return (TRUE);
	i = 0;
	path = ft_strdup(SPEAKER_PATH);
	if (!path)
		return (TRUE);
	while (i < SPEAKER_FRAME)
	{
		path[22] = i + '0';
		txtr->speaker[i].img = mlx_png_file_to_image(data->mlx, path,
								&txtr->speaker[i].size.x, &txtr->speaker[i].size.y);
		i ++;
	}
	free(path);
	return (FALSE);


}

t_bool	init_texture(t_data *data, t_parse *psg)
{
	data->map.txt = ft_calloc(6, sizeof(t_texture));
	if (!data->map.txt)
		return (TRUE);
	data->map.txt[0].img = mlx_png_file_to_image(data->mlx, psg->ress[0],
			&data->map.txt[0].size.x, &data->map.txt[0].size.y);
	data->map.txt[1].img = mlx_png_file_to_image(data->mlx, psg->ress[1],
			&data->map.txt[1].size.x, &data->map.txt[1].size.y);
	data->map.txt[2].img = mlx_png_file_to_image(data->mlx, psg->ress[2],
			&data->map.txt[2].size.x, &data->map.txt[2].size.y);
	data->map.txt[3].img = mlx_png_file_to_image(data->mlx, psg->ress[3],
			&data->map.txt[3].size.x, &data->map.txt[3].size.y);
	data->map.txt[4].img = mlx_png_file_to_image(data->mlx, DOOR_CLS_PATH_TXT,
			&data->map.txt[4].size.x, &data->map.txt[4].size.y);
	data->map.txt[5].img = mlx_png_file_to_image(data->mlx, DOOR_OP_PATH_TXT,
			&data->map.txt[5].size.x, &data->map.txt[5].size.y);
	
	return (FALSE);
}

t_bool	init_data(t_data *data, t_parse *psg, uint8_t *mu_code, t_coord	*mu_stereo)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (parsing("maps/test_square.cub", psg))
		return (TRUE);
	data->psg = psg;
	data->screen = init_screen();
	if (color_convert_rgb_hex(&data->map.floor.argb, data->psg->ress[4])
		|| color_convert_rgb_hex(&data->map.sky.argb, data->psg->ress[5])
		|| !data->screen
		|| init_texture(data, psg)
		|| init_anim_txtr(data, &data->map.anim_txtr))
		return (TRUE);
	data->map.content = psg->map;
	data->player.pos = psg->pos;
	data->player.dir = convert_card_to_grad(psg->card);
	data->player.target = WALL;
	data->hud.rotate_mm = TRUE;
	data->hud.start_anim = time_now();
	data->input = 0;
	data->map.size = ft_map_len(psg->map);
	data->fps.time = time_now();
	data->hud.mu_code = mu_code;
	pthread_mutex_init(&data->hud.mumu_code, NULL);
	data->hud.mu_stereo = mu_stereo;
	pthread_mutex_init(&data->hud.mumu_stereo, NULL);

	return (FALSE);
}
