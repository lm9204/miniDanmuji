/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:59:03 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/26 14:17:25 by yeondcho         ###   ########.fr       */
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
		handle_error("bash: cannot allocate memory: Not enough space");
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	name_len = i;
	res->name = malloc(sizeof(char) * (name_len + 1));
	ft_strlcpy(res->name, env, name_len + 1);
	res->value = ft_strdup(&env[name_len + 1]);
	res->next = NULL;
	return (res);
}
