/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_rc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:01:10 by mbico             #+#    #+#             */
/*   Updated: 2024/12/14 19:57:12 by mbico            ###   ########.fr       */
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
