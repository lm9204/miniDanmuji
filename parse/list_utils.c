/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:46:58 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/03 17:08:29 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clear_redirect(t_redirect *redirect)
{
	free(redirect->file);
	if (redirect->type == 4)
	{
		free(redirect->new_file);
		free(redirect->new_file_path);
	}
}

void	clear_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmds[i])
	{
		free(cmd->cmds[i]);
		i++;
	}
	i = 0;
	free(cmd->cmds);
	free(cmd->flags);
	free(cmd);
}

void	clear_head(t_list **head)
{
	t_redirect	*redirect;
	t_list		*ptr;
	t_list		*next;

	ptr = *head;
	while (ptr)
	{
		next = ptr->next;
		if (ptr->flag == 0)
			clear_cmds(ptr->content);
		if (ptr->flag == 2)
		{
			redirect = ptr->content;
			clear_redirect(redirect);
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
