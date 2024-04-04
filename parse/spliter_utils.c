/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:02:13 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/04 14:53:54 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	splitable_symbol_len(const char *cmds, int len)
{
	if (len == 0)
	{
		if (is_symbol(cmds) < 3 && cmds[len] != '|')
			return (2);
		return (1);
	}
	return (0);
}

int	findquotes(char *s, int quote)
{
	int	i;
	int	target;

	i = 0;
	if (quote == 1)
		target = '"';
	else if (quote == 2)
		target = '\'';
	else
		target = quote;
	while (s[i] && s[i] != target)
		i++;
	if (s[i] == target)
		return (i + 1);
	handle_error("syntax error");
	return (-1);
}

int	ft_isquotes(char c)
{
	// const char	quotes[3] = {'"', '\'', 0};

	if (c == '"')
		return (1);
	if (c == '\'')
		return (2);
	return (0);
}
