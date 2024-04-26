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

static int	split_cmds_size(char **cmds)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], ' ') != NULL)
			count += word_count(cmds[i]);
		count++;
		i++;
	}
	return (count);
}

char	**split_cmds_space(char **cmds)
{
	char	**res;
	char	**tmp;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = split_cmds_size(cmds);
	printf("size: %d\n", size);
	res = malloc(sizeof(char *) * (size + 1));
	if (res == NULL)
		return (NULL);
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], ' ') != NULL)
		{
			tmp = ft_split(cmds[i++], ' ');
			while (*tmp)
				res[j++] = *tmp++;
			// free(tmp);
			continue ;
		}
		else
			res[j++] = ft_strdup(cmds[i++]);
	}
	res[j] = NULL;
	return (res);
}

