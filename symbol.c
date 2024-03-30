/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:54:11 by yeondcho          #+#    #+#             */
/*   Updated: 2024/03/30 20:18:37 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_symbol(char *token)
{
	const char	*redirect_symbol[] = {"<", ">", "<<", ">>", 0};
	const char	*pipe = "|";
	int			i;

	if (ft_strncmp(pipe, token, ft_strlen(token) + 1) == 0)
		return (1);
	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(redirect_symbol[i], token, ft_strlen(token) + 1) == 0)
			return (2);
		i++;
	}
	return (0);
}

int	get_symbol_idx(char **tokens)
{
	int		idx;
	int		type;
	int		count_cmds;

	idx = 0;
	count_cmds = 0;
	while (tokens[idx])
	{
		type = is_symbol(tokens[idx]);
		if (type == 1 || type == 2)
			return (count_cmds);
		else
			count_cmds++;
		idx++;
	}
	return (0);
}