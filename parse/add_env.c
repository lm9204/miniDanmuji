/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_needle_to_haystack.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:59:03 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/24 16:22:36 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_equal_sign(char *needle)
{
	int	i;

	i = 0;
	while (needle[i])
	{
		if (needle[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	front_or_back_of_equal_sign(char *needle)
{
	int	front;
	int	back;

	front = 0;
	back = 0;
	while (*needle != '=')
	{
		needle++;
		front++;
	}
	needle++;
	while (*needle)
	{
		needle++;
		back++;
	}
	if (front && back)
		return (1);
	return (0);
}

int	check_env(char *env)
{
	if (!is_equal_sign(env))
		return (0);
	if (!front_or_back_of_equal_sign(env))
		return (0);
	return (1);
}

//env가 "a=./a.out" 이런 식으로 들어오면 그대로 envp_2d_ary 마지막에 추가
char	**add_env(char **envp_2d_ary, char *env)
{
	char	**res;
	int		column;
	int		i;

	if (!check_env(env))
		return (NULL);
	column = cnt_column_line(envp_2d_ary);
	res = (char **)malloc(sizeof(char *) * (column + 1 + 1));
	i = -1;
	while (envp_2d_ary[++i])
		res[i] = envp_2d_ary[i];
	res[i] = env;
	res[i + 1] = (char *)NULL;
	free(envp_2d_ary);
	return (res);
}
