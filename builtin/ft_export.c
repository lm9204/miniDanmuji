/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:45:32 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/16 15:03:08 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_list(t_env **head);
static void	export_env(t_env **head, char *cmd);
static void	add_to_list(t_env **head, t_env *new);

void	ft_export(t_env **head, char **cmd)
{
	int	i;

	i = 1;
	if (cmd == NULL || ft_strlen(cmd[1]) == 0)
		export_list(head);
	else
	{
		while (cmd[i])
		{
			export_env(head, cmd[i]);
			i++;
		}
	}
}

static void	export_list(t_env **head)
{
	t_env	*ptr;

	ptr = *head;
	while (ptr)
	{
		ft_putstr_fd(ptr->name, 1);
		if (ptr->value)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd(ptr->value, 1);
		}
		write(1, "\n", 1);
		ptr = ptr->next;
	}
}

static void	export_env(t_env **head, char *cmd)
{
	t_env	*new;
	t_env	*ptr;
	char	**res;

	res = ft_split(cmd, '=');
	ptr = find_env(head, res[0]);
	if (ptr)
	{
		free(ptr->value);
		ptr->value = res[1];
		return ;
	}
	new = malloc(sizeof(t_env));
	if (new == NULL)
		handle_error("malloc error");
	if (res[0] == NULL)
	{
		new->name = cmd;
		new->value = NULL;
	}
	else
	{
		new->name = res[0];
		new->value = res[1];
	}
	free(res);
	new->next = NULL;
	add_to_list(head, new);
}

static void	add_to_list(t_env **head, t_env *new)
{
	t_env	*ptr;

	ptr = *head;
	if (new == NULL)
		return ;
	if (ptr == NULL)
	{
		*head = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
