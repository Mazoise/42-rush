/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:28:24 by mchardin          #+#    #+#             */
/*   Updated: 2021/12/11 16:23:01 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char *
	ft_strjoin(char *s1, char *s2)
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
	str = malloc(sizeof (char *) * (i + j + 1));
	if (!str)
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

size_t
	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

void
	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int
	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned const char)s1[i] - (unsigned const char)s2[i]);
		else if (i == n || (s1[i] == 0 && s2[i] == 0))
			return (0);
		i++;
	}
	return (0);
}
