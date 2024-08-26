/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:03:01 by mbico             #+#    #+#             */
/*   Updated: 2024/08/25 04:42:17 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_matrix	ft_init_matrix(int row, int col, t_data *data)
{
	int			i;
	t_matrix	m;

	m.row = row;
	m.col = col;
	m.content = ft_calloc(sizeof(double *), row);
	if (!m.content)
		ft_close(65307, data);
	i = 0;
	while (i < row)
	{
		m.content[i] = ft_calloc(sizeof(double), col);
		if (!m.content[i])
			return (m);
		i ++;
	}
	return (m);
}

void	ft_clear_matrix(t_matrix *m)
{
	int			i;

	i = 0;
	while (i < m->row)
	{
		free(m->content[i]);
		i ++;
	}
	free(m->content);
}
