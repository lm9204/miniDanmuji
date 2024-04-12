/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:46:58 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/10 18:44:08 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	clear_head(t_list **head)
{
	t_redirect	*redirect;
	t_list		*ptr;
	t_list		*next;
	t_cmd		*cmd;

	ptr = *head;
	while (ptr)
	{
		next = ptr->next;
		if (ptr->flag == 0)
		{
			cmd = ptr->content;
			clear_cmds(cmd->cmds);
			free(cmd);
		}
		if (ptr->flag == 2)
		{
			redirect = ptr->content;
			free(redirect->file);
			free(redirect);
		}
		free(ptr);
		ptr = next;
	}
	*head = NULL;
}

void	free_env_list(t_env **head)
{
	t_env	*ptr;
	t_env	*tmp;

	ptr = *head;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

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
