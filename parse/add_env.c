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

void	addenv(t_env **env_head, char *env)
{
	t_env	*new;
	t_env	*ptr;

	if (!check_env(env))
		return ;
	new = create_env_node(env);
	ptr = *env_head;
	if (ptr == NULL)
	{
		*env_head = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_env	*create_env_node(char *env)
{
	t_env	*res;
	int		name_len;
	int		i;

	res = malloc(sizeof(t_env));
	if (res == NULL)
		handle_error("Malloc Error");
	i = 0;
	while (env[i] != '=')
		i++;
	name_len = i++;
	res->name = malloc(sizeof(char) * (name_len + 1));
	ft_strlcpy(res->name, env, name_len + 1);
	res->value = ft_strdup(&env[name_len + 1]);
	res->next = NULL;
	return (res);
}

//env가 "a=./a.out" 이런 식으로 들어오면 그대로 envp_2d_ary 마지막에 추가
// char	**add_env(char **envp_2d_ary, char *env)
// {
// 	char	**res;
// 	int		column;
// 	int		i;

// 	if (!check_env(env))
// 		return (NULL);
// 	column = cnt_column_line(envp_2d_ary);
// 	res = (char **)malloc(sizeof(char *) * (column + 1 + 1));
// 	i = -1;
// 	while (envp_2d_ary[++i])
// 		res[i] = envp_2d_ary[i];
// 	res[i] = env;
// 	res[i + 1] = (char *)NULL;
// 	free(envp_2d_ary);
// 	return (res);
// }
