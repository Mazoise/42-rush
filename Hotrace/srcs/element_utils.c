/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:14:30 by mchardin          #+#    #+#             */
/*   Updated: 2021/12/11 16:12:18 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int
	side(t_element *elem)
{
	if (!elem->parent)
		return (0);
	if (elem->parent->child[RIGHT] == elem)
		return (RIGHT);
	return (LEFT);
}

t_element *
	get_brother(t_element *elem)
{
	if (!elem->parent)
		return (0);
	return (elem->parent->child[!side(elem)]);
}

t_element *
	get_grand_parent(t_element *elem)
{
	if (elem->parent)
		return (elem->parent->parent);
	return (0);
}

t_element *
	get_uncle(t_element *elem)
{
	if (!elem->parent)
		return (0);
	return (get_brother(elem->parent));
}
