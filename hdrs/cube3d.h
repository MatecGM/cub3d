/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:49:38 by mbico             #+#    #+#             */
/*   Updated: 2024/09/11 19:29:44 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft.h"
# include "../MacroLibX/includes/mlx.h"
# include <stdio.h>
# include <math.h>
# include <sys/time.h>


# define WIDTH 1280
# define HEIGHT 720

# define MESH_WIDTH 100
# define MESH_HEIGHT 100

# define FOV_X 90
# define FOV_Y 90

# define PI 3.14159265359

# define RENDER_DISTANCE 1

typedef struct s_coord{
	double	x;
	double	y;
}	t_coord;

typedef struct s_dcoord{
	int	x;
	int	y;
}	t_dcoord;

typedef	struct s_raycast{
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
	

	double time;
	double oldTime;
	double moveSpeed;
	double rotSpeed;
	
} t_raycast;

typedef struct s_data{
	void		*mlx;
	void		*win;
	int			**map;
	t_coord		pos;
	int			map_width;
	int			map_height;
	t_raycast	*raycast;
}	t_data;

typedef struct s_matrix
{
	int		row;
	int		col;
	double	**content;
}		t_matrix;

void			print_background(t_data *data);
void			put_wall(t_data *data);
int				ft_close(int keycode, t_data *data);
int				round_mutiple(int nb, int mutiple);
void			raycasting(t_data *data);
unsigned int	get_time_ms(void);

#endif