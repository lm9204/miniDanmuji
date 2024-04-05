/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:48:26 by yeondcho          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/05 19:11:15 by seongjko         ###   ########.fr       */
=======
/*   Updated: 2024/04/04 22:01:25 by yeondcho         ###   ########.fr       */
>>>>>>> 8be87d0e1721d9598eb2b5053fb3d719b32c0c7f
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	seperate_word(char *cmds, int *i, int *count, int *isword);
static char	*checkcmd(t_env **head, char *cmd);
static char	*ft_cutcmds(const char *cmds, int *idx);
static int	count_cmds(char *cmds);

static char	*checkcmd(t_env **head, char *cmd)
{
	char	*res;
	int		quote;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = expand_len(head, cmd);
	printf("expectlen:%d\n", len);
	res = malloc(sizeof(char) * (len + 1));
	while (i < len && j < (int)ft_strlen(cmd))
	{
		quote = 0;
		if (ft_isquotes(cmd[j]))
		{
			quote = cmd[j];
			j++;
		}
		i += expand(head, &res[i], &cmd[j], quote);
		j += findquotes(&cmd[j], quote);
	}
	printf("i:%d\n", i);
	return (res);
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
		if (isquotes && cmds[len - 1] && cmds[len - 1] == isquotes \
		&& cmds[len] == ' ')
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

char	**split_cmds(char *cmds, t_env **envp)
{
	char	**res;
	char	*tmp;
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
		tmp = ft_cutcmds(&cmds[idx], &idx);
		res[i] = checkcmd(envp, tmp);
		printf("%d:%s\n", i, res[i]);
		free(tmp);
		i++;
	}
	res[i] = NULL;
	return (res);
}
