/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:51:21 by yeondcho          #+#    #+#             */
/*   Updated: 2024/03/29 15:53:17 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**split_cmds(char *cmds);
static void	checkcmd(char *cmd);
static int	findquotes(char *s, int quote);
static int	ft_isquotes(char c, const char quotes[]);
static char	*ft_cutcmds(const char *cmds, const char quotes[], int *idx);
static int	count_cmds(char *cmds, const char q[]);

static void	checkcmd(char *cmd)
{
	const char	quotes[3] = {'\'', '"', 0};

	while (*cmd)
	{
		if (ft_isquotes(*cmd, quotes)) // 환경변수 따옴표 제거 할 때 확장여부 확인하기
			ft_strlcpy(cmd, cmd + 1, ft_strlen(cmd));
		else
			cmd++;
	}
}

static int	findquotes(char *s, int quote)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == quote)
			return (i + 1);
		i++;
	}
	return (0);
}

char	**split_cmds(char *cmds)
{
	const char	quotes[3] = {'"', '\'', 0};
	char		**res;
	int			size;
	int			idx;
	int			i;

	size = count_cmds(cmds, quotes);
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	idx = 0;
	while (i < size)
	{
		while (cmds[idx] && cmds[idx] == ' ')
			idx++;
		res[i] = ft_cutcmds(&cmds[idx], quotes, &idx);
		checkcmd(res[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

static int	ft_isquotes(char c, const char quotes[])
{
	int	i;

	i = 0;
	while (quotes[i])
	{
		if (c == quotes[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_cutcmds(const char *cmds, const char quotes[], int *idx)
{
	char	*word;
	int		isquotes;
	int		len;

	len = 0;
	isquotes = 0;
	while (cmds[len])
	{
		if (isquotes && cmds[len] == isquotes)
		{
			if (cmds[len + 1] == ' ')
				break ;
		}
		if (!isquotes && ft_isquotes(cmds[len], quotes))
			isquotes = cmds[len];
		if (!isquotes && cmds[len] == ' ')
			break ;
		len++;
	}
	word = ft_allocword(cmds, len);
	*idx += len + 1;
	return (word);
}

static int	count_cmds(char *cmds, const char q[])
{
	int	count;
	int	isword;
	int	i;

	i = -1;
	count = 0;
	isword = 0;
	while (cmds[++i])
	{
		if (ft_isquotes(cmds[i], q))
		{
			if (findquotes(&cmds[i + 1], cmds[i]) == 0)
				return (-1);
			i += findquotes(&cmds[i + 1], cmds[i]);
			if (!isword)
				count++;
			isword = 1;
		}
		else if (!isword && cmds[i] != ' ')
		{
			isword = 1;
			count++;
		}
		else if (isword && cmds[i] == ' ')
			isword = 0;
	}
	return (count);
}

// int	main(void)
// {
// 	t_list	*head;
// 	char	*data;
// 	char	**res;
// 	int		i;

// 	head = NULL;
// 	data = readline("minishell $");
// 	res = split_cmds(data);
// 	i = 0;
// 	parse_to_node(&head, res);
// 	print_list(&head);
	 
// }
