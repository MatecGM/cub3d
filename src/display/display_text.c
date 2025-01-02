/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:25:13 by gadelbes          #+#    #+#             */
/*   Updated: 2025/01/02 14:31:55 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_argb	color;
	int32_t	target;

	color.argb = 0xFF000000;
	if (wh.rpos.x < 0 || wh.rpos.x >= data->map.size.x || wh.rpos.y < 0
		|| wh.rpos.y >= data->map.size.y)
		wh.rpos = (t_dcoord){0, 0};
	target = data->map.content[wh.rpos.y][wh.rpos.x];
	if (target == 1)
		color = all_text_rel_color(data, wh, ptr, data->map.txt);
	return (color);
}
