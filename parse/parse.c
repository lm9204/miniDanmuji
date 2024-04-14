/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:30:33 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/14 21:57:24 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand(t_env **head, char *output, char *cmd, char quote)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (cmd[i] && cmd[i] != quote)
	{
		if (ft_isquotes(quote) != 2 && cmd[i] == '$')
		{
			tmp = expand_symbol(head, &cmd[i + 1]);
			if (tmp)
				ft_strlcpy(&output[len], tmp, ft_strlen(tmp) + 1);
			i += get_word_len(&cmd[i + 1]) + 1;
			len += ft_strlen(tmp);
			continue ;
		}
		output[len++] = cmd[i++];
	}
	output[len] = 0;
	return (len);
}

char	*expand_symbol(t_env **head, char *cmd)
{
	t_env	*ptr;

	// if (cmd[0] == '?')
	// 	return (data->exit_status);
	ptr = find_env(head, cmd);
	if (ptr == NULL)
		return (NULL);
	return (ptr->value);
}

int	expand_len(t_env **head, char *cmd)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = sub_quote_len(cmd, cmd[0]);
	while (cmd[i])
	{
		j = i;
		if (cmd[0] != '\'' && cmd[i] == '$')
		{
			// if (cmd[i + 1] == '?')
			// 	return (ft_strlen(data->exit_status));
			while (cmd[j + 1] && cmd[j + 1] != ' ' && !ft_isquotes(cmd[j + 1]))
				j++;
			len += find_env_len(head, &cmd[i + 1]);
			i = j;
		}
		else
			len++;
		i++;
	}
	return (len);
}

int	sub_quote_len(char *cmd, char quote)
{
	int	i;

	i = 1;
	if (!ft_isquotes(quote))
		return (0);
	while (cmd[i] && cmd[i] != quote)
		i++;
	if (cmd[i] == quote)
		return (-2);
	return (-1);
}

int	get_word_len(char *word)
{
	int	i;

	i = 0;
	if (word[0] == ' ' || ft_isquotes(word[0]))
		i++;
	while (word[i])
	{
		if (word[i] == ' ' || ft_isquotes(word[i]))
			return (i);
		i++;
	}
	return (i);
}
