/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:16:16 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/29 15:03:51 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmds(char **cmds)
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

int	get_word_len(char *word)
{
	int	i;

	i = 0;
	if (word[0] == '?')
		return (1);
	if (word[0] == ' ')
		return (1);
	while (word[i])
	{
		if (word[i] == ' ' || ft_isquotes(word[i]))
			return (i);
		i++;
	}
	return (i);
}
