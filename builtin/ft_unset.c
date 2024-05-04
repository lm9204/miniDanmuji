/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:59:30 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/04 15:38:13 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_env(t_env **head, char *cmd)
{
	t_env	*prev;
	t_env	*ptr;

	prev = NULL;
	ptr = *head;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, cmd, ft_strlen(cmd) + 1) == 0)
		{
			if (!prev)
				*head = ptr->next;
			else
				prev->next = ptr->next;
			free(ptr->name);
			if (ptr->value)
				free(ptr->value);
			free(ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

int	ft_unset(t_env **head, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		unset_env(head, cmd[i]);
		i++;
	}
	return (0);
}
