/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssys_speaker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 21:16:00 by mbico             #+#    #+#             */
/*   Updated: 2024/12/14 19:47:36 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <math.h>

t_coord	get_speaker_coord(t_map map, uint32_t occ)
{
	t_dcoord	ptr;

	ptr.y = 0;
	while (map.content[ptr.y][0] != -1)
	{
		ptr.x = 0;
		while (map.content[ptr.y][ptr.x] != -1)
		{
			if (occ == 0 && map.content[ptr.y][ptr.x] == 5)
				return ((t_coord){ptr.x + 0.5, ptr.y + 0.5});
			else if (map.content[ptr.y][ptr.x] == 5)
				occ --;
			ptr.x ++;
		}
		ptr.y ++;
	}
	return ((t_coord){-1, -1});
}

t_coord	get_infl(t_coord spk, t_player player, t_coord infl)
{
	double	dist;
	double	rad;
	double	orr;

	dist = sqrt(pow(player.pos.x - spk.x, 2) + pow(player.pos.y - spk.y, 2));
	rad = atan2(player.pos.y - spk.y, player.pos.x - spk.x);
	orr = sin(fabs(player.dir - rad) - PI);
	infl.x += (PI / 2.0 + orr * 1.2) / ((double)dist * 1500.) * 500.;
	infl.y += (PI / 2.0 - orr * 1.2) / ((double)dist * 1500.) * 500.;
	return (infl);
}

void	speaker_stereo(t_data *data)
{
	t_coord		p;
	uint32_t	i;
	t_coord		infl;
	
	p = get_speaker_coord(data->map, 0);
	i = 1;
	infl = (t_coord){0, 0};
	while (p.x != -1)
	{
		infl = get_infl(p, data->player, infl);
		p = get_speaker_coord(data->map, i);
		i ++;
	}
	mutex_set_coord(data->hud.mu_stereo, infl, &data->hud.mumu_stereo);
}
