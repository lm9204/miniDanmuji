/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:01:32 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/01 20:57:35 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*init_one_line(char *line)
{
	char	*res;
	int		line_len;

	line_len = ft_strlen(line);
	res = (char *)malloc(sizeof(char) * (line_len + 1));
	ft_strlcpy(res, line, line_len + 1);
	*(res + line_len) = (char)NULL;
	return (res);
}

char	**init_envp(char **envp)
{
	int		column;
	int		i;
	char	**envp_2d_ary;

	column = cnt_column_line(envp);
	envp_2d_ary = (char **)malloc(sizeof(char *) * (column + 1));
	i = -1;
	while (envp[++i])
		envp_2d_ary[i] = init_one_line(envp[i]);
	envp_2d_ary[i] = NULL;
	return (envp_2d_ary);
}
