/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:01:32 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 16:03:33 by yeondcho         ###   ########.fr       */
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
	int		i;
	int		name_len;
	int		value_len;

	i = 0;
	name_len = ft_strlen(env->name);
	value_len = ft_strlen(env->value) + 1;
	res = malloc(sizeof(char) * (name_len + value_len + 2));
	if (res == NULL)
		handle_error("malloc error");
	while (i < name_len)
	{
		res[i] = env->name[i];
		i++;
	}
	res[i++] = '=';
	while (i < name_len + value_len + 1)
	{
		res[i] = env->value[i - name_len - 1];
		i++;
	}
	res[i] = 0;
	return (res);
}
