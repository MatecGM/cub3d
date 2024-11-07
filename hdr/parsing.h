/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:38:13 by mbico             #+#    #+#             */
/*   Updated: 2024/11/08 00:19:17 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef enum e_verif
{
    NO,
    SO,
    WE,
    EA,
    F,
    C,
}            t_verif;

int verif_wall(char **map, int x, int y, int limit);
int	verif_data(char **map, int y, char *name);

int find_wall(char **map, int x, int y, int find_nb);
int	find_map(char **map, int x, int y);

int	count_max_x(char **map, int y);
t_bool	**tab_size_x(char **map, int y, t_bool **tab);
int	tab_size_y(char **map, int y);
t_bool	**tab_map(char **map, int y, int x, t_bool **tab);

int	verif_png(char *str);
int	fill_id(char *ligne, char **id, t_verif param);
int	one_ligne(char **id, char *ligne);
char **tab_id(char **map, int y, int nb);

int	number_rgb(char **id_tab, int nb);
int	verif_rgb(char **id_tab);
char find_orentation(char **map, int y);
int	parsing(char *path);

//UTILS


int     ft_without_n(char c);
char    *dup_without_n(const char *src);
int     ft_is_space(char c);
int     sdigit_comma(int i);
int     count_char(char *str, char c);
int     count_tab(char **tab);
#endif