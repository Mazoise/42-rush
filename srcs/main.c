/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 11:22:45 by mchardin          #+#    #+#             */
/*   Updated: 2021/12/11 16:34:18 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int
	loop(char **key, char *line, int state, t_map *map)
{
	if (!line[0] && state == FILL_KEY)
	{
		state = FIND;
		free(line);
	}
	else if (state == FILL_KEY)
	{
		*key = line;
		state = FILL_VALUE;
	}
	else if (state == FILL_VALUE)
	{
		map_insert(make_pair(*key, line), map);
		state = FILL_KEY;
	}
	else
		print_value(line, map);
	return (state);
}

int
	main(void)
{
	int		state;
	char	*line;
	t_map	map;
	char	*key;
	int		ret;

	line = 0;
	state = FILL_KEY;
	ret = 1;
	key = 0;
	ft_bzero(&map, sizeof(map));
	map.root = empty_elem(0);
	while (ret)
	{
		ret = get_next_line(0, &line);
		state = loop(&key, line, state, &map);
	}
}
