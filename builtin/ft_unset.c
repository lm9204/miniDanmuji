/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:59:30 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/12 16:30:06 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_env **head, char *cmd)
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
			free(ptr->name);
			if (ptr->value)
				free(ptr->value);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}
