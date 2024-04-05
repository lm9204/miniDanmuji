/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:46:58 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/02 15:10:25 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void clear_cmds(char **cmds);

static void clear_cmds(char **cmds)
{
    int i;

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

void free_env_list(t_env **head)
{
    t_env   *tmp;

    while (head) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
    }
}
