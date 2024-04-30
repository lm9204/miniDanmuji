/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:56:28 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/30 17:06:13 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_env(t_env **env_head, char *name)
{
	t_env	*ptr;

	ptr = *env_head;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, name, ft_strlen(ptr->name) + 1) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int	find_env_len(t_data *data, char *name)
{
	t_env	*ptr;
	char	*tmp;

	if (name[0] == ' ')
		return (0);
	if (name[0] == '?')
		return (ft_strlen(data->exit_status));
	if (name[0] == '$')
		return (1);
	tmp = cut_expand(name);
	ptr = find_env(&data->env_head, tmp);
	free(tmp);
	if (ptr == NULL)
		return (0);
	return (ft_strlen(ptr->value));
}
