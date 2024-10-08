/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:39:50 by mbico             #+#    #+#             */
/*   Updated: 2024/10/09 01:30:44 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

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
	void		*mlx;
	void		*win;
	void		*img;
	t_bool		**map;
	t_coord		pos;
	double		dir;
	int			map_width;
	int			map_height;
	t_rc		rc;
}				t_data;

int				ft_keydown(int kc, void *d);
void			displaying(t_data *data);
void			print_line(t_data *data, t_dcoord p1, t_dcoord p2, int color);
t_coord			get_first_wall_x(t_data *data, double dir);
t_coord			get_first_wall_y(t_data *data, double dir);
t_coord			get_first_wall(t_data *data, double dir);

int				map_write_check(char **map, int x, int y);
int				verif_wall(char **map, int x, int y);
int				verif_data(char **map, int y);

int				find_wall(char **map, int x, int y, int find_nb);
int				find_map(char **map, int x, int y);

int				count_max_x(char **map, int y);
t_bool			**tab_size_x(char **map, int y, t_bool **tab);
int				tab_size_y(char **map, int y, int x);
t_bool			**tab_map(char **map, int y, int x, t_bool **tab);
t_bool			**parsing(char *path);

#endif
