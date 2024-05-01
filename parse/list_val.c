/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:16:16 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/30 12:46:17 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	syntax_error(t_data *data, char *cmd)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(cmd, 1);
	ft_putendl_fd("'", 1);
	if (data->exit_status)
		free(data->exit_status);
	data->exit_status = ft_strdup("258");
}

static int	validate_is_symbol(char *file)
{
	const char	*symbol[] = {"<<", ">>", "<", ">", 0};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(symbol[i], file, ft_strlen(symbol[i]) + 1) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

static int	validate_redirect(t_data *data, t_redirect *node)
{
	if (!node->file || validate_is_symbol(node->file) \
	|| ft_strncmp(node->file, "|", 2) == 0)
	{
		if (!node->file)
			syntax_error(data, "newline");
		else
			syntax_error(data, node->file);
		return (0);
	}
	return (1);
}

void	expand_node(t_data *data, t_cmd *cmds)
{
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	while (cmds->cmds[i])
	{
		tmp = cmds->cmds[i];
		cmds->cmds[i] = checkcmd(data, cmds->cmds[i], &cmds->flags[i]);
		free(tmp);
		i++;
	}
	split = split_cmds_space(cmds, i);
	while (i >= 0)
	{
		free(cmds->cmds[i--]);
	}
	free(cmds->cmds);
	cmds->cmds = split;
}

int	validate_node_list(t_data *data)
{
	t_list	*ptr;
	int		pipe_flag;
	int		return_value;

	pipe_flag = 0;
	ptr = data->head;
	return_value = 1;
	while (ptr)
	{
		if (ptr->flag == 0)
			expand_node(data, ptr->content);
		if (!pipe_flag && ptr->flag == 1)
			pipe_flag = 1;
		else if (pipe_flag && ptr->flag != 1)
			pipe_flag = 0;
		else if (pipe_flag && ptr->flag == 1)
		{
			syntax_error(data, "|");
			return (0);
		}
		else if (ptr->flag == 2)
			return_value = validate_redirect(data, ptr->content);
		ptr = ptr->next;
	}
	return (return_value);
}
