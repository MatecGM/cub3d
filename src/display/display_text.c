/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:25:13 by gadelbes          #+#    #+#             */
/*   Updated: 2024/12/11 18:33:43 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cube3d.h>

t_argb	all_text_rel_color(t_data *data, t_wh wh, t_dcoord ptr, t_texture *txt)
{
	t_argb	color;

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
	t_argb	color;

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
		color = mono_text_rel_color(data, wh, ptr, \
		data->map.anim_txtr.speaker[0]);
	else if (target == SPEAKER_ON)
		color = mono_text_rel_color(data, wh, ptr, \
		data->map.anim_txtr.speaker[data->hud.frame_speaker]);
	else if (target == WALL)
		color = all_text_rel_color(data, wh, ptr, data->map.txt);
	return (color);
}
