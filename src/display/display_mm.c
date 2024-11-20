/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:19:58 by mbico             #+#    #+#             */
/*   Updated: 2024/11/18 21:42:00 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <math.h>

void	display_viewray(t_data *data, t_dcoord rel_pos);

t_bool	circle_calc(t_dcoord sptr)
{
	uint32_t	dist;

	dist = sqrt(pow(sptr.x - 75, 2) + pow(sptr.y - 75, 2));
	if (dist <= 75)
		return (TRUE);
	return (FALSE);
}

void	display_map_mm(t_data *data)
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
			if (ptr.x >= 0 && ptr.x < data->map.size.x && ptr.y >= 0 && ptr.y < data->map.size.y && data->map.content[(int)ptr.y][(int)ptr.x] && circle_calc(sptr) || (!(ptr.x >= 0 && ptr.x < data->map.size.x && ptr.y >= 0 && ptr.y < data->map.size.y) && circle_calc(sptr)))
				put_pixel_inscreen(data, sptr.x + 45, sptr.y + 45, (t_argb)0xCC000000);
			if (sptr.x > (150.0 / RD_MM) * i.x)
				i.x += 0.1;
			sptr.x ++;
		}
		if (sptr.y > (150.0 / RD_MM) * i.y)
			i.y += 0.1;
		sptr.y ++;
	}
	t_dcoord rel_pos;
	rel_pos.x = 75 + 45;
	rel_pos.y = 75 + 45;
	display_viewray(data, rel_pos);
	put_pixel_inscreen(data, 75 + 45, 75 + 45, (t_argb)0xFFFFFFFF);
	
}

void	display_viewray(t_data *data, t_dcoord rel_pos)
{
	t_wh		wh;
	t_dcoord	rel_hit;
	int			i;
	double		dir;

	i = 0;
	rel_hit.y = data->rc.ay * 150  + 45;
	rel_hit.x = data->rc.ax * 150 + 45;
	print_line(data, rel_pos, rel_hit, (t_argb)0xFF00FF00);
	while (i < 150)
	{
		dir = (data->player.dir - PI / 4.0) + ((PI / 2.0) / (double)150 * i);
		if (dir < 0)
			dir += 2 * PI;
		else if (dir >= PI * 2)
			dir -= 2 * PI;
		wh = dda(data, dir);
		rel_hit.x = (wh.hit.x - data->player.pos.x) * 150. / 8. + 120 - 1;
		rel_hit.y = (wh.hit.y - data->player.pos.y) * 150. / 8. + 120;
		print_line(data, rel_pos, rel_hit, (t_argb)0xFF6666FF);
		i ++;
	}
}

void	display_player_mm(t_data *data)

{
}
