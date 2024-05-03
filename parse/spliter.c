/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:48:26 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/03 17:36:43 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	seperate_word(char *cmds, int *i, int *count, int *isword);
static char	*ft_cutcmds(const char *cmds, int *idx);
static int	count_cmds(char *cmds);

char	*checkcmd(t_data *data, char *cmd, int *quote_flag)
{
	char	*res;
	int		len;
	int		return_value;

	if (cmd == NULL)
		return (NULL);
	len = expand_len(data, cmd);
	if (len == 0)
		return (NULL);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	return_value = expand(data, res, cmd, 0);
	if (quote_flag)
		*quote_flag = return_value;
	return (res);
}

static char	*ft_cutcmds(const char *cmds, int *idx)
{
	char	*word;
	int		len;

	len = 0;
	while (cmds[len])
	{
		if (ft_isquotes(cmds[len]) \
		&& findquotes(&cmds[len + 1], cmds[len]) != -1)
			len += findquotes(&cmds[len + 1], cmds[len]);
		if (is_symbol(&cmds[len]) || cmds[len] == '|')
		{
			len += splitable_symbol_len(&cmds[len], len);
			break ;
		}
		if (cmds[len] == ' ')
			break ;
		len++;
	}
	word = ft_allocword(cmds, len);
	*idx += len;
	return (word);
}

static void	seperate_word(char *cmds, int *i, int *count, int *isword)
{
	if (ft_isquotes(cmds[*i]) && findquotes(&cmds[*i + 1], cmds[*i]) != -1)
	{
		*i += findquotes(&cmds[*i + 1], cmds[*i]);
		if (!(*isword))
			(*count)++;
		*isword = 1;
	}
	else if (is_symbol(&cmds[*i]) || cmds[*i] == '|')
	{
		if (is_symbol(&cmds[*i]) != 0)
			*i += is_symbol(&cmds[*i]) < 3;
		*isword = 0;
		(*count)++;
	}
	else if (!(*isword) && cmds[*i] != ' ')
	{
		*isword = 1;
		(*count)++;
	}
	else if (*isword && (cmds[*i] == ' '))
		*isword = 0;
}

static int	count_cmds(char *cmds)
{
	int	count;
	int	isword;
	int	i;

	i = -1;
	count = 0;
	isword = 0;
	while (cmds[++i])
		seperate_word(cmds, &i, &count, &isword);
	return (count);
}

char	**split_cmds(char *cmds)
{
	char	**res;
	int		size;
	int		idx;
	int		i;

	size = count_cmds(cmds);
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	idx = 0;
	while (i < size)
	{
		while (cmds[idx] && cmds[idx] == ' ')
			idx++;
		res[i] = ft_cutcmds(&cmds[idx], &idx);
		i++;
	}
	res[i] = NULL;
	return (res);
}
