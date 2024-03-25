/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_haystack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:01:32 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/24 15:32:47 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_column_line(char **envp)
{
	int cnt;

	cnt = 0;
	while (*envp)
	{
		envp++;
		cnt++;
	}
	return (cnt);
}

char	*init_hay(char *hay)
{
	char	*res;
	int		hay_len;

	hay_len = ft_strlen(hay);
	res = (char *)malloc(sizeof(char) * (hay_len + 1));
	ft_strlcpy(res, hay, hay_len + 1);
	*(res + hay_len + 1) = (char)NULL;
	return (res);
}

char	**init_haystack(char **envp)
{
	int		column;
	int		i;
	char	**haystack;

	column = cnt_column_line(envp);
	haystack = (char **)malloc(sizeof(char *) * (column + 1));
	i = -1;
	while (envp[++i])
		haystack[i] = init_hay(envp[i]);
	haystack[i] = NULL;
	return (haystack);
}
