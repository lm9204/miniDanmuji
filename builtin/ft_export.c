/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:45:32 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/26 16:12:49 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_to_list(t_env **head, t_env *new);
static int	export_env(t_data *data, char *cmd);

int	ft_export(t_data *data, char **cmd)
{
	t_env	*ptr;
	int		return_value;
	int		i;

	i = 1;
	ptr = data->env_head;
	return_value = 0;
	if (cmd == NULL || ft_strlen(cmd[1]) == 0)
	{
		while (ptr)
		{
			printf("%s", ptr->name);
			if (ptr->value)
				printf("=\"%s\"", ptr->value);
			printf("\n");
			ptr = ptr->next;
		}
	}
	else
		while (cmd[i])
			if (export_env(data, cmd[i++]))
				return_value = 1;
	return (return_value);
}

static int	validate_name(char *cmd)
{
	int	return_value;
	int	i;

	i = 0;
	return_value = 0;
	if (ft_isdigit(cmd[0]))
		return_value = 1;
	while (cmd[i] && !return_value)
	{
		if (cmd[i] != '_' && !ft_isalnum(cmd[i]))
			return_value = 1;
		if (cmd[i] == ' ')
			return_value = 1;
		i++;
	}
	if (return_value)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (return_value);
}

static char	**split_cmd(char *cmd)
{
	char	**res;
	int		i;
	int		idx;

	i = 0;
	idx = 1;
	res = malloc(sizeof(char *) * 3);
	if (res == NULL)
		return (NULL);
	while (cmd[i] && cmd[i] != '=')
		i++;
	res[0] = ft_substr(cmd, 0, i);
	if (cmd[i] == '=')
		res[idx++] = ft_substr(cmd, i + 1, ft_strlen(cmd) - i);
	res[idx] = 0;
	return (res);
}

static int	export_env(t_data *data, char *cmd)
{
	char	**res;
	t_env	*new;
	t_env	*ptr;

	res = split_cmd(cmd);
	if (res == NULL || validate_name(res[0]))
		return (1);
	ptr = find_env(&data->env_head, res[0]);
	if (ptr)
	{
		if (!res[1])
			return (0);
		free(ptr->value);
		ptr->value = res[1];
		return (0);
	}
	new = malloc(sizeof(t_env));
	if (new == NULL)
		handle_error("malloc error");
	new->name = res[0];
	new->value = res[1];
	new->next = NULL;
	free(res);
	add_to_list(&data->env_head, new);
	return (0);
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
