/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:49:38 by mbico             #+#    #+#             */
/*   Updated: 2024/09/20 07:23:17 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>

# define WIDTH 1280
# define HEIGHT 720

# define MESH_WIDTH 100
# define MESH_HEIGHT 100

# define FOV_X 90
# define FOV_Y 90

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

typedef struct s_raycast
{
	t_coord		dir;
	t_coord		plane;
	t_coord		ray_dir;
	t_dcoord	map;
	t_coord		side_dist;
	t_coord		delta_dist;
	double		perp_wall_dist;
	t_dcoord	step;
	t_bool		hit;
	int			side;

	double		time;
	double		oldTime;
	double		moveSpeed;
	double		rotSpeed;

}				t_raycast;

typedef struct s_img_data
{
	void		*mlx_img;
	int			width;
	int			height;
}				t_img_data;

typedef struct s_txtr
{
	t_img_data	nwall;
	t_img_data	swall;
	t_img_data	wwall;
	t_img_data	ewall;
}				t_txtr;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	t_bool		**map;
	t_coord		pos;
	int			map_width;
	int			map_height;
	t_txtr		txtr;
	t_raycast	*raycast;
}				t_data;

typedef struct s_matrix
{
	int			row;
	int			col;
	double		**content;
}				t_matrix;

void			print_background(t_data *data);
void			put_wall(t_data *data);
int				ft_close(int keycode, void *d);
int				round_mutiple(int nb, int mutiple);
void			raycasting(t_data *data);
unsigned int	get_time_ms(void);

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
