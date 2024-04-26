/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:45:32 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/26 14:23:07 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_list(t_env **head);
static void	export_env(t_data *data, char *cmd);
static void	add_to_list(t_env **head, t_env *new);

void	ft_export(t_data *data, char **cmd)
{
	int	i;

	i = 1;
	if (cmd == NULL || ft_strlen(cmd[1]) == 0)
		export_list(&data->env_head);
	else
	{
		while (cmd[i])
		{
			export_env(data, cmd[i]);
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
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(ptr->value, 1);
			ft_putstr_fd("\"", 1);
		}
		write(1, "\n", 1);
		ptr = ptr->next;
	}
}

// static void	

static void	export_env(t_data *data, char *cmd)
{
	char	**res;
	t_env	*new;
	t_env	*ptr;

	res = ft_split(cmd, '=');
	ptr = find_env(&data->env_head, res[0]);
	if (ptr)
	{
		free(ptr->value);
		ptr->value = res[1];
		return ;
	}
	new = malloc(sizeof(t_env));
	if (new == NULL)
		handle_error("malloc error");
	if (res[1] == NULL)
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
	add_to_list(&data->env_head, new);
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
