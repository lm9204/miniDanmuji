/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:02:13 by yeondcho          #+#    #+#             */
/*   Updated: 2024/03/30 20:45:57 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	i = 0;
	while (s[i])
	{
		if (s[i] == quote)
			return (i + 1);
		i++;
	}
	handle_error("syntax error");
	return (-1);
}

int	ft_isquotes(char c)
{
	const char	quotes[3] = {'"', '\'', 0};
	int			i;

	i = 0;
	while (quotes[i])
	{
		if (c == quotes[i])
			return (1);
		i++;
	}
	return (0);
}
