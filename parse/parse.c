/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:30:33 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/02 15:16:58 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	validate_parse_list(t_list **head)
// {
	
// }

// int	parse_newline(char *newline)
// {

// }

int	find_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

char	*expand_symbol(char *symbol, char **envp, int len)
{
	char	*res;
	char	*env;
	int		size;
	int		i;

	len = 0;
	env = find_env(envp, symbol);
	i = 0;
	size = 0;
	res = 0;
	while (symbol[i])
	{
		if (symbol[i] == ' ')
			break ;
		i++;
	}
	return (NULL);
}

int	search_expandable(char *cmd)
{
	int	flag;
	int	len;
	int	i;

	i = 0;
	flag = 0;
	len = 0;
	while (cmd[i])
	{
		if (!flag && ft_isquotes(cmd[i]) == 2)
			flag = 1;
		else if (flag && ft_isquotes(cmd[i]) == 2)
			flag = 0;
		if (!flag && !ft_isquotes(cmd[i]) && cmd[i] == '$')
		{
			
		}
		i++;
	}
	return (0);
}
