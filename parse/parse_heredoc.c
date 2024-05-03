/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:28:38 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/03 17:51:02 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_expand(t_data *data, char *output, char *cmd)
{
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '$' && is_expandable(&cmd[i + 1]) > 0)
			len += expand_join(data, &cmd[i + 1], &output[len], &i);
		else
			output[len++] = cmd[i];
	}
	output[len] = 0;
}

static int	expand_heredoc_len(t_data *data, char *cmd)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && is_expandable(&cmd[i + 1]) > 0)
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

char	*heredoc_newline(t_data *data, char *cmd)
{
	char	*res;
	int		len;

	if (cmd == NULL)
		return (NULL);
	len = expand_heredoc_len(data, cmd);
	if (len == 0)
		return (NULL);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	heredoc_expand(data, res, cmd);
	free(cmd);
	return (res);
}
