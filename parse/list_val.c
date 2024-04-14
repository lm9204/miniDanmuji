/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:16:16 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/14 17:43:09 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	syntax_error(char *cmd)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(cmd, 1);
	ft_putendl_fd("'", 1);
	// exit(258);
	//data->exit_status = "258";
}

static void	validate_redirect(t_redirect *node)
{
	if (is_symbol(node->file) || ft_strncmp(node->file, "|", 2) == 0)
		syntax_error(node->file);
}

void	validate_node_list(t_list **head)
{
	t_list	*ptr;
	int		pipe_flag;

	pipe_flag = 0;
	ptr = *head;
	while (ptr)
	{
		if (!pipe_flag && ptr->flag == 1)
			pipe_flag = 1;
		else if (pipe_flag && ptr->flag != 1)
			pipe_flag = 0;
		else if (pipe_flag && ptr->flag == 1)
			syntax_error("|");
		else if (ptr->flag == 2)
			validate_redirect(ptr->content);
		ptr = ptr->next;
	}
}
