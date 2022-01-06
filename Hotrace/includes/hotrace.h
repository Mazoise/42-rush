/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 11:03:37 by mchardin          #+#    #+#             */
/*   Updated: 2021/12/11 17:06:07 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "gnl.h"

# define BLACK 0
# define RED 1
# define LEFT 0
# define RIGHT 1
# define FILL_KEY 0
# define FILL_VALUE 1
# define FIND 2

typedef struct s_pair
{
	char				*value;
	char				*key;
}	t_pair;

typedef struct s_element
{
	t_pair				pair;
	struct s_element	*child[2];
	struct s_element	*parent;
	int					color;
}	t_element;

typedef struct s_map
{
	t_element			*root;
	size_t				size;
}	t_map;

void
ft_bzero(void *b, size_t n);
void
ft_putstr_fd(char *s, int fd);
t_pair
make_pair(char *key, char *value);
t_element
*find_elem(char *key, t_map *map);
void
print_value(char *key, t_map *map);
t_element
*empty_elem(t_element *parent);
void
map_insert(t_pair new_pair, t_map *map);
int
side(t_element *elem);
t_element
*get_grand_parent(t_element *elem);
t_element
*get_brother(t_element *elem);
t_element
*get_uncle(t_element *elem);
int
ft_strcmp(const char *s1, const char *s2);
size_t
ft_strlen(const char *s);

#endif