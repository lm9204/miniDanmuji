/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:46:58 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/04 15:41:14 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_flags(t_cmd *cmd, int size);
static void	list_add(t_list **head, void *content, int type);
static void	list_redirect_add(t_list **head, char **cmds, int size);
static void	list_cmd_add(t_list **head, char **cmds, int size);

static void	init_flags(t_cmd *cmd, int size)
{
	int	i;

	i = 0;
	cmd->flags = malloc(sizeof(int) * (size + 1));
	if (cmd->flags == NULL)
		handle_error("malloc error");
	while (i < size)
	{
		cmd->flags[i++] = 0;
	}
	cmd->flags[i] = 0;
}

static void	list_cmd_add(t_list **head, char **cmds, int size)
{
	t_cmd	*cmd;
	int		cmds_size;
	int		ci;
	int		i;

	cmds_size = token_cmds_len(cmds);
	if (cmds_size != 0 && size != 0)
	{
		cmd = malloc(sizeof(t_cmd));
		cmd->cmds = ft_calloc(sizeof(char *), cmds_size + 1);
		init_flags(cmd, cmds_size);
		if (cmd == NULL || cmd->cmds == NULL)
			handle_error("malloc error");
		ci = 0;
		i = 0;
		while (i < size)
		{
			if (!is_symbol(cmds[i]))
				cmd->cmds[ci++] = cmds[i++];
			else
				i += 2;
		}
		list_add(head, cmd, 0);
	}
	list_redirect_add(head, cmds, size);
}

static void	list_redirect_add(t_list **head, char **cmds, int size)
{
	t_redirect	*res;
	int			i;

	i = 0;
	while (i < size)
	{
		if (is_symbol(cmds[i]))
		{
			res = malloc(sizeof(t_redirect));
			res->type = is_symbol(cmds[i]) - 1;
			res->file = cmds[i + 1];
			list_add(head, res, 2);
			free(cmds[i++]);
		}
		i++;
	}
}

static void	list_add(t_list **head, void *content, int type)
{
	t_list	*ptr;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	new->content = content;
	new->flag = type;
	new->next = NULL;
	ptr = *head;
	if (ptr == NULL)
	{
		*head = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	parse_to_node(t_list **head, char **tokens)
{
	int	i;
	int	target;

	i = 0;
	while (tokens[i])
	{
		target = get_pipe_idx(&tokens[i]);
		if (target == -1)
		{
			list_cmd_add(head, &tokens[i], tokenlen(&tokens[i]));
			return ;
		}
		else
			list_cmd_add(head, &tokens[i], target);
		list_add(head, NULL, 1);
		i += target;
		free(tokens[i]);
		i++;
	}
}
