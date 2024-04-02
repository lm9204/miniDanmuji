/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmv_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:03:38 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/31 18:00:28 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**rmv_env(char **envp_2d_ary, char *env)
{
	char	**res;
	int		column;
	int		e_i;
	int		r_i;

	column = cnt_column_line(envp_2d_ary);
	res = (char **)malloc(sizeof(char *) * column);
	r_i = 0;
	e_i = 0;
	while (envp_2d_ary[e_i])
	{
		if (!ft_strncmp(envp_2d_ary[e_i], env, ft_strlen(env)))
		{
			//free 왜 하는 거임?
			free(envp_2d_ary[e_i]);
			e_i++;
		}
		else
			res[r_i++] = envp_2d_ary[e_i++];
	}
	*(res + column) = NULL;
	free(envp_2d_ary);
	return (res);
}
