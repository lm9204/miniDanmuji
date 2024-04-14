/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:25:50 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/17 19:45:58 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strchr(const char *s, int c)
{
	int	cnt;

	cnt = 0;
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (-1);
		cnt++;
		s++;
	}
	return (cnt);
}

char	*gnl_strndup(char *str, int len)
{
	int			i;
	char		*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
		p[i++] = *str++;
	p[i] = '\0';
	return (p);
}

char	*gnl_strjoin(char *dest, char *append)
{
	char	*p;
	int		cnt1;
	int		cnt2;
	int		i;

	i = 0;
	cnt1 = gnl_strlen(dest);
	cnt2 = gnl_strlen(append);
	p = (char *)malloc(cnt1 + cnt2 + 1);
	while (*dest)
		p[i++] = *dest++;
	while (*append)
		p[i++] = *append++;
	p[i] = '\0';
	return (p);
}

size_t	gnl_strlen(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (*str)
	{
		str++;
		cnt++;
	}
	return (cnt);
}
