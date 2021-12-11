/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 11:22:45 by mchardin          #+#    #+#             */
/*   Updated: 2021/12/11 13:25:00 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int		main()
{
	int		state = FILL_KEY;
	char	*line = 0;
	t_map	map;
	char	*key;
	t_pair	new_pair;

	ft_bzero(&map, sizeof(map));
	map.root = empty_elem(0);
	while (get_next_line(0, &line) > 0)
	{
		if(!line[0] && state == FILL_VALUE)
		{
			state = FIND;
			free(line);
		}
		else if (state == FILL_KEY)
		{
			key = line;
			state = FILL_VALUE;
		}
		else if (state == FILL_VALUE)
		{
			new_pair = make_pair(key, line);
			map_insert(new_pair, &map);
		}
		else
			print_value(line, &map);
	}
}
