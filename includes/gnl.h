/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:36:20 by mchardin          #+#    #+#             */
/*   Updated: 2021/12/11 11:20:04 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define B BUFFER_SIZE

typedef struct	s_buf
{
	int		r;
	char	buf[1][BUFFER_SIZE + 1];
}				t_buf;

int				get_next_line(int fd, char **line);
char			*ft_strjoin(char *s1, char *s2);

#endif