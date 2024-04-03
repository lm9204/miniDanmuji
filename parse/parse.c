/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:30:33 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/03 13:47:09 by yeondcho         ###   ########.fr       */
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

char	*expand_symbol(t_env **head, char *cmd, int len)
{
	char	*res;
	char	*env;
	int		size;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		j = 0;
		env = search_expand(head, &cmd[i]);
		if (env)
			j = ft_strlcpy(res, env, ft_strlen(env));
		else
		{
			while (cmd[i] != ' ')
				;
		}
		res[i] = cmd[i];
		i++;
	}
	return (NULL);
}

int	expand_len(t_env **head, char *cmd)
{
	int	flag;    
	int	len;
	int	i;
	int	j;

	i = 0;
	flag = 0;
	len = 0;
	while (cmd[i])
	{
		j = 0;
		if (!flag && ft_isquotes(cmd[i]) == 2)
			flag = 1;
		else if (flag && ft_isquotes(cmd[i]) == 2)
			flag = 0;
		if (!flag && !ft_isquotes(cmd[i]) && cmd[i] == '$')
		{
			while (cmd[j] != ' ')
				j++;
			len += find_env_len(head, cmd[i], j) - j;
		}
		i++;
	}
	return (len);
}

char	*search_expand(t_env **head, char *cmd)
{
	int	flag;
	int	len;
	int	i;
	int	j;

	i = 0;
	flag = 0;
	len = 0;
	while (cmd[i])
	{
		j = 0;
		if (!flag && ft_isquotes(cmd[i]) == 2)
			flag = 1;
		else if (flag && ft_isquotes(cmd[i]) == 2)
			flag = 0;
		if (!flag && !ft_isquotes(cmd[i]) && cmd[i] == '$')
		{
			while (cmd[j] != ' ')
				j++;
			len += find_env_len(head, cmd[i], j) - j;
		}
		i++;
	}
	return (len);
}
