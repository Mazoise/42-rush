/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:28:24 by mchardin          #+#    #+#             */
/*   Updated: 2021/12/11 13:36:29 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char
*ft_strjoin(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;
	char			*temp_s1;

	i = 0;
	j = 0;
	temp_s1 = s1;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	if (!(str = malloc(sizeof(char*) * (i + j + 1))))
	{
		free(s1);
		return (0);
	}
	while (s1 && *temp_s1)
		*str++ = *temp_s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = 0;
	free(s1);
	return (str - i - j);
}

void
ft_bzero(void *b, size_t n)
{
	unsigned char	*a;
	size_t			i;

	a = b;
	i = 0;
	while (i < n)
	{
		a[i] = 0;
		i++;
	}
}

void
ft_putstr_fd(char *s, int fd)
{
	int n;

	n = 0;
	while (s[n])
		n++;
	write(fd, s, n);
}
