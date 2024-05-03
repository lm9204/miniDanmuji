/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:30:33 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/03 17:38:43 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_join(t_data *data, char *expand, char *output, int *i)
{
	char	*tmp;

	tmp = expand_symbol(data, expand);
	if (tmp)
		ft_strlcpy(output, tmp, ft_strlen(tmp) + 1);
	*i += get_word_len(expand);
	return (ft_strlen(tmp));
}

int	expand(t_data *data, char *output, char *cmd, int quote)
{
	int		quote_flag;
	int		len;
	int		i;

	i = -1;
	len = 0;
	quote_flag = 0;
	while (cmd[++i])
	{
		if (!quote && ft_isquotes(cmd[i]) \
		&& findquotes(&cmd[i + 1], cmd[i]) != -1)
			quote = ft_isquotes(cmd[i]);
		else if (quote && ft_isquotes(cmd[i]) == quote)
			quote = 0;
		else if (quote != 2 && cmd[i] == '$' && is_expandable(&cmd[i + 1]) > 0)
		{
			if (quote == 0)
				quote_flag = 1;
			len += expand_join(data, &cmd[i + 1], &output[len], &i);
		}
		else
			output[len++] = cmd[i];
	}
	output[len] = 0;
	return (quote_flag);
}

char	*expand_symbol(t_data *data, char *cmd)
{
	t_env	*ptr;
	char	*dollar_sign;
	char	*tmp;

	dollar_sign = "$";
	if (cmd[0] == ' ' && ft_strlen(cmd) == 1)
	{
		dollar_sign = "$ ";
		return (dollar_sign);
	}
	if (ft_strlen(cmd) == 1 && (cmd[0] == 0 || ft_isquotes(cmd[0])))
		return (dollar_sign);
	if (cmd[0] == '?')
		return (data->exit_status);
	tmp = cut_expand(cmd);
	ptr = find_env(&data->env_head, tmp);
	free(tmp);
	if (ptr == NULL)
		return (NULL);
	return (ptr->value);
}

int	expand_len(t_data *data, char *cmd)
{
	int	q;
	int	len;
	int	i;

	i = 0;
	len = 0;
	q = 0;
	while (cmd[i])
	{
		if (!q && ft_isquotes(cmd[i]) && findquotes(&cmd[i + 1], cmd[i]) != -1)
			q = ft_isquotes(cmd[i]);
		else if (q && ft_isquotes(cmd[i]) == q)
			q = 0;
		else if (q != 2 && cmd[i] == '$' && is_expandable(&cmd[i + 1]) > 0)
		{
			len += find_env_len(data, &cmd[i + 1]);
			i += get_word_len(&cmd[i + 1]) + 1;
			continue ;
		}
		else
			len++;
		i++;
	}
	return (len);
}
