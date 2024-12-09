/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_rc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:01:10 by mbico             #+#    #+#             */
/*   Updated: 2024/12/09 20:33:11 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cube3d.h>

int	get_wall_size(t_coord pos, t_coord hit)
{
	double	dist;
	int		size;

	dist = sqrt(pow(hit.x - pos.x, 2.0) + pow(hit.y - pos.y, 2.0));
	size = 1 / (double)dist * (HEIGHT / 2.0);
	return (size);
}

t_argb	get_png_pixel(t_data *data, t_texture txt, double x, t_dcoord ptr)
{
	t_dcoord	rel;
	int			margin;
	t_argb		color;

	margin = (HEIGHT - ptr.y);
	rel.x = (int)((x - floor(x)) * txt.size.x);
	rel.y = (int)(((ptr.x - margin) / (double)(ptr.y - margin)) * txt.size.y);
	color.argb = mlx_get_image_pixel(data->mlx, txt.img, rel.x, rel.y);
	return (color);
}

t_argb	all_text_rel_color(t_data *data, t_wh wh, t_dcoord ptr, t_texture *txt)
{
	t_argb color;

	color.argb = 0xFF000000;
	if (wh.face == NO)
		color = get_png_pixel(data, txt[NO], wh.hit.x, ptr);
	else if (wh.face == SO)
		color = get_png_pixel(data, txt[SO], -wh.hit.x, ptr);
	else if (wh.face == WE)
		color = get_png_pixel(data, txt[WE], -wh.hit.y, ptr);
	else if (wh.face == EA)
		color = get_png_pixel(data, txt[EA], wh.hit.y, ptr);
	return (color);
}

t_argb	mono_text_rel_color(t_data *data, t_wh wh, t_dcoord ptr, t_texture txt)
{
	t_argb color;

	color.argb = 0xFF000000;
	if (wh.face == NO)
		color = get_png_pixel(data, txt, wh.hit.x, ptr);
	else if (wh.face == SO)
		color = get_png_pixel(data, txt, -wh.hit.x, ptr);
	else if (wh.face == WE)
		color = get_png_pixel(data, txt, -wh.hit.y, ptr);
	else if (wh.face == EA)
		color = get_png_pixel(data, txt, wh.hit.y, ptr);
	return (color);
}

t_argb	texture_rel_color(t_data *data, t_wh wh, t_dcoord ptr)
{
	t_argb		color;
	t_wall		target;

	color.argb = 0xFF000000;
	target = data->map.content[wh.rpos.y][wh.rpos.x]; 
	if (target == DOOR_CLS)
		color = mono_text_rel_color(data, wh, ptr, data->map.txt[4]);
	else if (target == DOOR_OP)
		color = mono_text_rel_color(data, wh, ptr, data->map.txt[5]);
	else if (target == SPEAKER_OFF)
		color = mono_text_rel_color(data, wh, ptr, data->map.anim_txtr.speaker[0]);
	else if (target == SPEAKER_ON)
		color = mono_text_rel_color(data, wh, ptr, data->map.anim_txtr.speaker[data->hud.frame_speaker]);
	else if (target == WALL)
		color = all_text_rel_color(data, wh, ptr, data->map.txt);
	return (color);
}

void	display_wall(t_data *data, int x, int size, t_wh wh)
{
	t_argb		color;
	t_dcoord	ptr;

	ptr.x = HEIGHT / 2 - size;
	ptr.y = HEIGHT / 2 + size;
	if (ptr.x < 0)
		ptr.x = 0;
	data->hud.frame_speaker = (time_now() - data->hud.start_anim) / 50 % SPEAKER_FRAME;
	while (ptr.x < ptr.y && ptr.x < HEIGHT)
	{
		color = texture_rel_color(data, wh, ptr);
		put_pixel_inscreen(data, x, ptr.x, color);
		ptr.x ++;
	}
}

void	display_rc(t_data *data)
{
	int		i;
	int		size;
	double	dir;
	t_wh	wh;

	i = 1;
	while (i < WIDTH)
	{
		dir = (data->player.dir - PI / 4.0) + ((PI / 2.0) / (double)WIDTH * i);
		if (dir < 0)
			dir += 2 * PI;
		else if (dir >= PI * 2)
			dir -= 2 * PI;
		wh = dda(data, dir);
		size = get_wall_size(data->player.pos, wh.hit);
		display_wall(data, i, size, wh);
		i++;
	}
}
