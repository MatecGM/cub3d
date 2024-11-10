/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:39:50 by mbico             #+#    #+#             */
/*   Updated: 2024/11/10 04:38:05 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "mlx.h"
# include <math.h>
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>

# include <parsing.h>

# define WIDTH 1280
# define HEIGHT 720

# define PI 3.14159265359

# define RENDER_DISTANCE 1

typedef struct s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct s_dcoord
{
	int			x;
	int			y;
}				t_dcoord;

typedef struct s_rc
{
	double	ax;
	double	ay;
}		t_rc;

typedef struct s_data
{
	__uint128_t	input;
	t_rc		rc;
	double		dir;
	t_coord		pos;
	t_parse		*psg;
	void		*mlx;
	void		*win;
	void		*img;
	t_bool		**map;
	int			map_width;
	int			map_height;
}				t_data;

int				ft_keydown(int kc, void *d);
void			displaying(t_data *data);
void			print_line(t_data *data, t_dcoord p1, t_dcoord p2, int color);
t_coord			get_first_wall_x(t_data *data, double dir);
t_coord			get_first_wall_y(t_data *data, double dir);
t_coord			get_first_wall(t_data *data, double dir);
int				keydown(int kc, void *d);
int				keyup(int kc, void *d);
void			put_pixel_inscreen(t_data *data, int x, int y, int color);
int				key_action(t_data *data);

void			display_player_mm(t_data *data);
void			display_map_mm(t_data *data);
void			display_rc(t_data *data);
t_bool			check_approx(double nb1, double nb2, int approx);
void			display_clear(t_data *data);

#endif
