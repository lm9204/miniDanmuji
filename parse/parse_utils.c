/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:16:16 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/30 16:58:25 by yeondcho         ###   ########.fr       */
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
	if (word[0] == '$')
		return (1);
	while (word[i])
	{
		if (word[i] == ' ' || ft_isalnum(word[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	is_expandable(char *word)
{
	int	i;

	i = 0;
	if (word[0] == '?')
		return (1);
	while (word[i])
	{
		if (word[i] == ' ' || ft_isalnum(word[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

char	*cut_expand(char *cmd)
{
	char	*res;
	int		size;
	int		i;

	i = 0;
	size = is_expandable(cmd);
	if (size == 0)
		return (NULL);
	res = malloc(sizeof(char) * (size + 1));
	if (res == NULL)
		return (NULL);
	while (i < size)
	{
		res[i] = cmd[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
