/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:01:32 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/06 14:49:32 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_list(t_env **head)
{
	t_env	*ptr;
	int		count;

	count = 0;
	ptr = *head;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

void	init_envp(t_env **env_head, char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return ;
	while (envp[i])
	{
		addenv(env_head, envp[i]);
		i++;
	}
}

char	**list_to_envp(t_env **head)
{
	t_env	*ptr;
	char	**res;
	int		len;
	int		i;

	len = count_list(head);
	res = malloc(sizeof (char *) * (len + 1));
	if (res == NULL)
		handle_error("malloc error");
	i = 0;
	ptr = *head;
	while (i < len && ptr)
	{
		res[i] = ft_env_to_char(ptr);
		ptr = ptr->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_env_to_char(t_env *env)
{
	char	*res;
	int		name_len;
	int		value_len;

	name_len = ft_strlen(env->name);
	value_len = ft_strlen(env->value);
	res = malloc(sizeof(char) * (name_len + value_len + 2));
	if (res == NULL)
		handle_error("malloc error");
	ft_memcpy(res, env->name, name_len);
	if (value_len > 0 || env->value != NULL)
		res[name_len++] = '=';
	ft_memcpy(res + name_len, env->value, value_len);
	res[name_len + value_len] = 0;
	return (res);
}
