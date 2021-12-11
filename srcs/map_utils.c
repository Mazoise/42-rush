/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:07:39 by mchardin          #+#    #+#             */
/*   Updated: 2021/12/11 16:02:37 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_pair
	make_pair(char *key, char *value)
{
	t_pair	new;

	new.key = key;
	new.value = value;
	return (new);
}

t_element *
	find_elem(char *key, t_map *map)
{
	t_element	*elem;
	int			res;

	elem = map->root;
	while (elem && elem->pair.value)
	{
		res = ft_strncmp(elem->pair.key, key, ft_strlen(key) + 1);
		if (!res)
			return (elem);
		elem = elem->child[res < 0];
	}
	return (0);
}

void
	print_value(char *key, t_map *map)
{
	t_element	*elem;

	elem = find_elem(key, map);
	if (elem)
	{
		ft_putstr_fd(elem->pair.value, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd(key, 1);
		ft_putstr_fd(": Not found.\n", 1);
	}
}

t_element *
	empty_elem(t_element *parent)
{
	t_element	*new;

	new = malloc(sizeof (t_element));
	ft_bzero(new, sizeof (*new));
	new->parent = parent;
	return (new);
}
