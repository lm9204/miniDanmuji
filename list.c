/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:46:58 by yeondcho          #+#    #+#             */
/*   Updated: 2024/03/30 20:51:29 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_add(t_list **head, void *content, int type);
static void	list_redirect_add(t_list **head, char *target, char *symbol);
static void	list_cmd_add(t_list **head, char **cmds, int size);

static void	list_cmd_add(t_list **head, char **cmds, int size)
{
	t_cmd	*cmd;
	int		cmds_size;
	int		ci;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	cmds_size = token_cmds_len(cmds);
	cmd->cmds = malloc(sizeof(char *) * (cmds_size + 1));
	if (cmd == NULL || cmd->cmds == NULL)
		exit(1);
	ci = 0;
	i = 0;
	while (i < size)
	{
		if (!is_symbol(cmds[i]))
			cmd->cmds[ci++] = cmds[i++];
		else
			i += 2;
	}
	cmd->cmds[ci] = 0;
	list_add(head, cmd, 0);
	i = -1;
	while (++i < size)
		if (is_symbol(cmds[i]))
			list_redirect_add(head, cmds[i + 1], cmds[i]);
}

static void	list_redirect_add(t_list **head, char *target, char *symbol)
{
	t_redirect	*res;
	int			i;

	res = malloc(sizeof(t_redirect));
	i = 0;
	res->type = is_symbol(symbol) - 1;
	res->file = target;
	list_add(head, res, 2);
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
		list_cmd_add(head, &tokens[i], target);
		list_add(head, NULL, 1);
		i += target;
		i++;
	}
}

void	print_list(t_list **head)
{
	const char	*redirect_symbol[] = {"<<", ">>", "<", ">", 0};
	t_list		*ptr;
	t_cmd		*cmd_ptr;
	t_redirect	*redirect_ptr;
	int			i;

	ptr = *head;
	while (ptr)
	{
		if (ptr->flag == 0)
		{
			i = 0;
			cmd_ptr = ptr->content;
			printf("cmds:\t");
			while (cmd_ptr->cmds[i])
			{
				printf(",%s,", cmd_ptr->cmds[i]);
				i++;
			}
			printf("\n");
		}
		if (ptr->flag == 1)
			printf("pipe:\t|\n");
		if (ptr->flag == 2)
		{
			redirect_ptr = ptr->content;
			printf("redir:\t%s %s\n", \
			redirect_symbol[redirect_ptr->type], redirect_ptr->file);
		}
		ptr = ptr->next;
	}
}
