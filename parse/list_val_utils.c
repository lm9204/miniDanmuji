/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_val_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:07:52 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/26 21:38:33 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	word_count(char *cmd)
{
	int	i;
	int	count;
	int	isword;

	i = 0;
	count = 0;
	isword = 0;
	while (cmd[i])
	{
		if (!isword && cmd[i] != ' ')
		{
			isword = 1;
			count++;
		}
		if (isword && cmd[i] == ' ')
			isword = 0;
		i++;
	}
	return (count);
}

static int	split_cmds_size(t_cmd *cmd, int og_size)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < og_size)
	{
		if (cmd->flags[i] && cmd->cmds[i] && ft_strchr(cmd->cmds[i], ' ') != NULL)
			count += word_count(cmd->cmds[i]);
		if (cmd->cmds[i])
			count++;
		i++;
	}
	return (count);
}

static void	insert_and_free(char **res, char **tmp, int *j)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		res[(*j)++] = tmp[i];
		free(tmp[i++]);
	}
	free(tmp);
}

char	**split_cmds_space(t_cmd *cmd, int og_size)
{
	char	**res;
	char	**tmp;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = split_cmds_size(cmd, og_size);
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		return (NULL);
	while (j < size)
	{
		if (cmd->flags[i] && cmd->cmds[i] && ft_strchr(cmd->cmds[i], ' ') != NULL)
		{
			tmp = ft_split(cmd->cmds[i++], ' ');
			insert_and_free(res, tmp, &j);
			continue ;
		}
		else if (cmd->cmds[i])
			res[j++] = ft_strdup(cmd->cmds[i++]);
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}

