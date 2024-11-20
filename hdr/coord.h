/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 04:20:40 by mbico             #+#    #+#             */
/*   Updated: 2024/11/17 15:48:40 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORD_H
# define COORD_H

# include <stdint.h>

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

typedef struct	s_circle
{
	t_coord		center;
	uint32_t	r;
	uint32_t	color;
}	t_circle;

#endif
