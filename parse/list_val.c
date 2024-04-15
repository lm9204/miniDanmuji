/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:16:16 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/15 18:59:00 by yeondcho         ###   ########.fr       */
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
	data->exit_status = "258";
}

static void	validate_redirect(t_data *data, t_redirect *node)
{
	if (is_symbol(node->file) || ft_strncmp(node->file, "|", 2) == 0)
		syntax_error(data, node->file);
}

void	validate_node_list(t_data *data)
{
	t_list	*ptr;
	int		pipe_flag;

	pipe_flag = 0;
	ptr = data->head;
	while (ptr)
	{
		if (!pipe_flag && ptr->flag == 1)
			pipe_flag = 1;
		else if (pipe_flag && ptr->flag != 1)
			pipe_flag = 0;
		else if (pipe_flag && ptr->flag == 1)
		{
			syntax_error(data, "|");
			return ;
		}
		else if (ptr->flag == 2)
		{
			validate_redirect(data, ptr->content);
			return ;
		}
		ptr = ptr->next;
	}
}
