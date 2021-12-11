/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:56:49 by mchardin          #+#    #+#             */
/*   Updated: 2021/12/11 16:56:39 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void
	rotate(t_element *rhs, int dir, t_map *map)
{
	t_element	*tmp;

	if (!rhs)
		return ;
	tmp = rhs->child[!dir];
	rhs->child[!dir] = tmp->child[dir];
	tmp->child[dir]->parent = rhs;
	tmp->child[dir] = rhs;
	tmp->parent = rhs->parent;
	if (!tmp->parent)
		map->root = tmp;
	else
		rhs->parent->child[side(rhs)] = tmp;
	tmp->child[dir] = rhs;
	rhs->parent = tmp;
}

void
	simple_insert(t_element *new_elem, t_map *map)
{
	t_element	*i;
	int			dir;

	i = map->root;
	if (!map->root->pair.value)
	{
		free(map->root);
		map->root = new_elem;
		return ;
	}
	while (i->pair.value)
	{
		dir = ft_strncmp(i->pair.key, new_elem->pair.key, ft_strlen(i->pair.key) + 1) < 0;
		if (i->child[dir] && i->child[dir]->pair.value)
			i = i->child[dir];
		else
		{
			free(i->child[dir]);
			i->child[dir] = new_elem;
			new_elem->parent = i;
			return ;
		}
	}
}

t_element *
	red_black_loop(t_element *elem, t_map *map)
{
	int			dir;
	t_element	*uncle;

	uncle = get_uncle(elem);
	dir = side(elem->parent);
	if (uncle && uncle->color == RED)
	{
		elem->parent->color = BLACK;
		uncle->color = BLACK;
		uncle->parent->color = RED;
		elem = get_grand_parent(elem);
	}
	else if (side(elem) == !dir)
	{
		elem = elem->parent;
		rotate(elem, dir, map);
	}
	else
	{
		elem->parent->color = BLACK;
		get_grand_parent(elem)->color = RED;
		elem = get_grand_parent(elem);
		rotate(elem, !dir, map);
	}
	return (elem);
}

void
	red_black(t_element *elem, t_map *map)
{
	if (map->root == elem)
	{
		elem->color = BLACK;
		return ;
	}
	while (elem != map->root && elem->parent->color == RED)
	{
		elem = red_black_loop(elem, map);
		map->root->color = BLACK;
	}
}

void
	map_insert(t_pair new_pair, t_map *map)
{
	t_element	*new_elem;

	new_elem = find_elem(new_pair.key, map);
	if (!new_elem)
	{
		new_elem = malloc(sizeof(t_element));
		new_elem->pair = new_pair;
		new_elem->child[LEFT] = empty_elem(new_elem);
		new_elem->child[RIGHT] = empty_elem(new_elem);
		simple_insert(new_elem, map);
		red_black(new_elem, map);
		map->size++;
	}
	else
	{
		free(new_elem->pair.value);
		new_elem->pair.value = new_pair.value;
	}
}
