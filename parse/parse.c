/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:30:33 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/24 21:05:47 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand(t_data *data, char *output, char *cmd, char quote)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	printf("quote:%c cmd:%s\n", quote, cmd);
	while (cmd[i] && cmd[i] != quote)
	{
		if (ft_isquotes(quote) != 2 && cmd[i] == '$')
		{
			tmp = expand_symbol(data, &cmd[i + 1]);
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

char	*expand_symbol(t_data *data, char *cmd)
{
	t_env	*ptr;

	if (cmd[0] == ' ')
		return ("$");
	if (cmd[0] == '?')
		return (data->exit_status);
	ptr = find_env(&data->env_head, cmd);
	if (ptr == NULL)
		return (NULL);
	return (ptr->value);
}

int	expand_len(t_data *data, char *cmd)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = sub_quote_len(cmd, cmd[0]);
	while (cmd[i])
	{
		j = i;
		if ((cmd[i - 1] != '\'' || (i == 0 && cmd[0] != '\'')) && cmd[i] == '$')
		{
			if (cmd[i + 1] == ' ')
				return (1);
			if (cmd[i + 1] == '?')
				return (ft_strlen(data->exit_status));
			while (cmd[j + 1] && cmd[j + 1] != ' ' && !ft_isquotes(cmd[j + 1]))
				j++;
			len += find_env_len(&data->env_head, &cmd[i + 1]);
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
	int	len;
	int	i;

	i = 0;
	len = 0;
	quote = 0;
	while (cmd[i])
	{
		if (ft_isquotes(cmd[i]))
		{
			i += findquotes(&cmd[i + 1], cmd[i]);
			len = -2;
		}
		i++;
	}
	return (len);
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
