/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:19:58 by mbico             #+#    #+#             */
/*   Updated: 2024/12/09 19:15:58 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <stdint.h>

void	display_wall_block(t_data *data, t_coord ptr, t_dcoord sptr, uint32_t **frame)
{
	if ((ptr.x >= 0 && ptr.x < data->map.size.x && ptr.y >= 0 && ptr.y < data->map.size.y))
	{
		if (data->map.content[(int)ptr.y][(int)ptr.x] == WALL)
			put_pixel_on_mm(frame, sptr.x, sptr.y, 0xCC000000);
		else if (data->map.content[(int)ptr.y][(int)ptr.x] == DOOR_CLS)
			put_pixel_on_mm(frame, sptr.x, sptr.y, 0xCCFF0000);
		else if (data->map.content[(int)ptr.y][(int)ptr.x] == DOOR_OP)
			put_pixel_on_mm(frame, sptr.x, sptr.y, 0xCC00FF00);
		else if (data->map.content[(int)ptr.y][(int)ptr.x] == SPEAKER_OFF)
			put_pixel_on_mm(frame, sptr.x, sptr.y, 0xCCFFCCCC);
		else if (data->map.content[(int)ptr.y][(int)ptr.x] == SPEAKER_ON)
			put_pixel_on_mm(frame, sptr.x, sptr.y, 0xCCFF00FF);

	}
	else if (!(ptr.x >= 0 && ptr.x < data->map.size.x && ptr.y >= 0 && ptr.y < data->map.size.y))
		put_pixel_on_mm(frame, sptr.x, sptr.y, 0xCC000000);
	
}

void	display_map_mm(t_data *data, uint32_t **frame)
{
	t_coord		ptr;
	t_dcoord	sptr;
	t_coord	i;

	sptr.y = 0;
	i.y = 0;
	while (sptr.y < 150)
	{
		sptr.x = 0;
		i.x = 0;
		ptr.y = data->player.pos.y - RD_MM / 2.0 + (double)i.y;
		while (sptr.x < 150)
		{
			ptr.x = data->player.pos.x - RD_MM / 2.0 + (double)i.x;
			display_wall_block(data, ptr, sptr, frame);
			if (sptr.x > (150.0 / RD_MM) * i.x)
				i.x += 0.1;
			sptr.x ++;
		}
		if (sptr.y > (150.0 / RD_MM) * i.y)
			i.y += 0.1;
		sptr.y ++;
	}
}

void	display_viewray(t_data *data, t_dcoord rel_pos, uint32_t **frame)
{
	t_wh		wh;
	t_dcoord	rel_hit;
	int			i;
	double		dir;

	i = 0;
	rel_hit.y = data->rc.ay * 150;
	rel_hit.x = data->rc.ax * 150;
	while (i < 150)
	{
		dir = (data->player.dir - PI / 4.0) + ((PI / 2.0) / (double)150 * i);
		if (dir < 0)
			dir += 2 * PI;
		else if (dir >= PI * 2)
			dir -= 2 * PI;
		wh = dda(data, dir);
		rel_hit.x = (wh.hit.x - data->player.pos.x) * 150. / 8. + 75 - 1;
		rel_hit.y = (wh.hit.y - data->player.pos.y) * 150. / 8. + 75;
		print_line_mm(frame, rel_pos, rel_hit, (t_argb)0xFF6666FF);
		i ++;
	}
}

void	display_mm(t_data *data)
{
	uint32_t	**frame;

	frame = init_mm();
	display_map_mm(data, frame);
	t_dcoord rel_pos;
	rel_pos.x = 75;
	rel_pos.y = 75;
	display_viewray(data, rel_pos, frame);
	if (data->hud.rotate_mm)
		frame = rotate_mm(frame, data->player.dir);
	display_mm_on_screen(data, frame);
	
}
