/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:56:28 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/26 17:17:05 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_env(t_env **env_head, char *name)
{
	t_env	*ptr;

	ptr = *env_head;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, name, ft_strlen(ptr->name)) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int	find_env_len(t_env **env_head, char *name)
{
	t_env	*ptr;

	if (name[0] == ' ')
		return (0);
	ptr = find_env(env_head, name);
	if (ptr == NULL)
		return (0);
	return (ft_strlen(ptr->value));
}
