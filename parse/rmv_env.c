/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmv_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:03:38 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/03 13:50:17 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rmv_env(t_env **env_head, char *name)
{
	t_env	*prev;
	t_env	*ptr;

	prev = NULL;
	ptr = *env_head;
	while (ptr)
	{
		if (prev)
			prev = ptr;
		if (ft_strncmp(ptr->name, name, ft_strlen(ptr->name) + 1) == 0)
		{
			if (!prev)
				*env_head = ptr->next;
			else
			{
				prev->next = ptr->next;
				free(ptr->name);
				if (ptr->value)
					free(ptr->value);
				free(ptr);
			}
			return ;
		}
		ptr = ptr->next;
	}
}
