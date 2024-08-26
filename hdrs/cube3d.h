/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:49:38 by mbico             #+#    #+#             */
/*   Updated: 2024/08/25 14:00:56 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>


# define WIDTH 1280
# define HEIGHT 720

# define MESH_WIDTH 100
# define MESH_HEIGHT 100

# define FOV_X 90
# define FOV_Y 90

# define RENDER_DISTANCE 10

typedef struct s_coord{
	double	x;
	double	y;
}	t_coord;

typedef struct s_data{
	void	*mlx;
	void	*win;
	t_coord *wall;
	t_coord	cam;
}	t_data;

typedef struct s_matrix
{
	int		row;
	int		col;
	double	**content;
}		t_matrix;

void	print_background(t_data *data);
void	put_wall(t_data *data, t_coord *wall, t_coord cam);
int		ft_close(int keycode, t_data *data);
int		round_mutiple(int nb, int mutiple);

#endif