/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:56:28 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 17:14:50 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_env(t_env **env_head, char *name, int len)
{
	t_env	*ptr;

	if (len == 0)
		len = ft_strlen(name);
	ptr = *env_head;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, name, len + 1) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int	find_env_len(t_env **env_head, char *name, int len)
{
	t_env	*ptr;

	ptr = find_env(env_head, name, len);
	if (ptr == NULL)
		return (0);
	return (ft_strlen(ptr->value));
}
