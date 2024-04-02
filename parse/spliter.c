/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:48:26 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/02 15:14:19 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	seperate_word(char *cmds, int *i, int *count, int *isword);
static void	checkcmd(char *cmd, char **envp);
static char	*ft_cutcmds(const char *cmds, int *idx);
static int	count_cmds(char *cmds);

static void	checkcmd(char *cmd, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = search_expandable(cmd);
	if (len)
	{
		cmd = expand_symbol(cmd, envp, len);
		return ;
	}
	while (cmd[i])
	{
		if (ft_isquotes(*cmd))
		{
			ft_strlcpy(cmd, cmd + 1, ft_strlen(cmd));
		}
		else
			cmd++;
	}
}

static char	*ft_cutcmds(const char *cmds, int *idx)
{
	char	*word;
	int		isquotes;
	int		len;

	len = 0;
	isquotes = 0;
	while (cmds[len])
	{
		if (isquotes && cmds[len] == isquotes && cmds[len + 1] == ' ')
			break ;
		if (!isquotes && ft_isquotes(cmds[len]))
			isquotes = cmds[len];
		if (!isquotes && (is_symbol(&cmds[len]) || cmds[len] == '|'))
		{
			len += splitable_symbol_len(&cmds[len], len);
			break ;
		}
		if (!isquotes && cmds[len] == ' ')
			break ;
		len++;
	}
	word = ft_allocword(cmds, len);
	*idx += len;
	return (word);
}

static void	seperate_word(char *cmds, int *i, int *count, int *isword)
{
	if (ft_isquotes(cmds[*i]) && findquotes(&cmds[*i + 1], cmds[*i]))
	{
		*i += findquotes(&cmds[*i + 1], cmds[*i]);
		if (!(*isword))
			(*count)++;
		*isword = 1;
	}
	else if (is_symbol(&cmds[*i]) || cmds[*i] == '|')
	{
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

char	**split_cmds(char *cmds, char **envp)
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
		checkcmd(res[i++], envp);
	}
	res[i] = NULL;
	return (res);
}
