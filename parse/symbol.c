/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:54:11 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/14 16:07:36 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_word(const char *line)
{
	if (is_symbol(line))
		return (0);
	return (1);
}

int	is_symbol(const char *token)
{
	const char	*symbol[] = {"<<", ">>", "<", ">", 0};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(symbol[i], token, ft_strlen(symbol[i])) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int	get_pipe_idx(char **tokens)
{
	int		idx;

	idx = 0;
	while (tokens[idx])
	{
		if (ft_strncmp(tokens[idx], "|", 1) == 0)
			return (idx);
		idx++;
	}
	return (-1);
}
