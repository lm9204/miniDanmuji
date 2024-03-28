/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:46:58 by yeondcho          #+#    #+#             */
/*   Updated: 2024/03/25 11:25:33 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_add(t_list **head, void *content, int type);
static void	list_redirect_add(t_list **head, char *target, char *symbol);
static void	list_cmd_add(t_list **head, char **cmds, int size);

static void	list_cmd_add(t_list **head, char **cmds, int size)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return ;
	cmd->cmds = malloc(sizeof(char *) * (size + 1));
	if (cmd->cmds == NULL)
		return ;
	while (i < size)
	{
		cmd->cmds[i] = cmds[i];
		i++;
	}
	cmd->cmds[i] = NULL;
	list_add(head, cmd, 0);
}

static void	list_redirect_add(t_list **head, char *target, char *symbol)
{
	const char	*redirect_symbol[] = {"<", ">", "<<", ">>", 0};
	t_redirect	*res;
	int			i;

	res = malloc(sizeof(t_redirect));
	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(redirect_symbol[i], symbol, 3) == 0)
			res->type = i;
		i++;
	}
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

void	print_list(t_list **head)
{
	const char	*redirect_symbol[] = {"<", ">", "<<", ">>", 0};
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
				printf("%s ", cmd_ptr->cmds[i]);
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

void	parse_to_node(t_list **head, char **tokens)
{
	int	i;
	int	symbol;
	int	target;

	i = 0;
	symbol = 0;
	while (tokens[i])
	{
		target = get_symbol_idx(&tokens[i]);
		symbol = is_symbol(tokens[i + target]);
		if (target > 0)
			list_cmd_add(head, &tokens[i], target);
		if (symbol == 1)
			list_add(head, NULL, 1);
		else if (symbol == 2)
		{
			list_redirect_add(head, tokens[i + target + 1], tokens[i + target]);
			i++;
		}
			i += target;
		i++;
	}
	if (!symbol)
		list_cmd_add(head, tokens, i);
}
