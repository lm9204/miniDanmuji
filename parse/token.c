/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:51:21 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/18 14:44:57 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenlen(char **tokens)
{
	int	len;

	len = 0;
	while (tokens[len])
		len++;
	return (len);
}

int	token_cmds_len(char **tokens)
{
	int	size;
	int	len;
	int	i;

	i = 0;
	len = 0;
	size = tokenlen(tokens);
	while (i < size && tokens[i])
	{
		if (!is_symbol(tokens[i]))
			len++;
		else
			i++;
		i++;
	}
	return (len);
}

void	print_env(t_env **head)
{
	t_env	*ptr;

	ptr = *head;
	while (ptr)
	{
		printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}
