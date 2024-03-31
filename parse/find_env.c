/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:56:28 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/31 16:40:52 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_env_pos(char *envp_1d_ary)
{
	while (*envp_1d_ary != '=')
		envp_1d_ary++;
	return (envp_1d_ary + 1);
}

//envp에 a="./a.out" 이런 식으로 정의되어 있다면
//find_env_in_envp_2d_ary(envp_2d_ary, "a") 이렇게 들어왔을 때
//""./a.out" 문자열을 리턴
//못 찾았다면 NULL값을 리턴

char	*find_env(char **envp_2d_ary, char *env)
{
	char	*res;
	char	*temp;
	int		env_len;

	while (*envp_2d_ary)
	{
		temp = *envp_2d_ary;
		if (!ft_strncmp(temp, env, ft_strlen(env)))
		{
			env_len = ft_strlen(find_env_pos(temp));
			res = (char *)malloc(sizeof(char) * (env_len + 1));
			ft_strlcpy(res, find_env_pos(temp), env_len + 1);
			*(res + env_len + 1) = (char)NULL;
			return (res);
		}
		envp_2d_ary++;
	}
	return (NULL);
}
