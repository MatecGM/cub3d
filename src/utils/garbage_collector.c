/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:14:12 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 17:16:00 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <cube3d.h>
#include <sys/cdefs.h>

t_gc	**get_gc(void)
{
	static t_gc	*gc;

	return (&gc);
}

t_gc	*gc_new(void *adr, t_bool istab)
{
	t_gc	*gc;

	gc = ft_calloc(sizeof(t_gc), 1);
	if (!gc)
		return (NULL);
	gc->adr = adr;
	gc->next = NULL;
	gc->istab = istab;
	return (gc);
}

void	gc_clear(t_gc *gc)
{
	if (!gc)
		return ;
	gc_clear(gc->next);
	if (gc->istab)
		ft_freetab(gc->adr, INT_MAX);
	else
		free(gc->adr);
}

t_bool	gc_addback(void *adr, t_bool istab)
{
	t_gc	*tmp;
	t_gc	**gc;
	t_gc	*new;

	gc = get_gc();
	new = gc_new(adr, istab);
	if (!new)
	{
		gc_clear(*gc);
		if (istab)
			ft_freetab(adr, INT_MAX);
		else
			free(adr);
		return (TRUE);
	}
	if (*gc == NULL)
	{
		*gc = new;
		return (FALSE);
	}
	tmp = *gc;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (FALSE);
}

void	__attribute__((destructor))	free_gc(void)
{
	t_gc	*gc;

	gc = *get_gc();
	gc_clear(gc);
}
