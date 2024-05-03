/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:45:32 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/03 16:35:55 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*new_env(char *name, char *value);
static int		export_env(t_data *data, char *cmd);

int	ft_export(t_data *data, char **cmd)
{
	int		return_value;
	int		i;

	i = 1;
	return_value = 0;
	if (cmd == NULL || ft_strlen(cmd[1]) == 0)
		export_list(list_to_envp(&data->env_head));
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
	if (ft_isdigit(cmd[0]) || cmd[0] == '=')
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
		ft_putstr_fd(PROMPT_MSG, 2);
		ft_putstr_fd("export: `", 2);
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
	if (i == 0)
		res[0] = ft_strdup("=");
	else
		res[0] = ft_substr(cmd, 0, i);
	if (cmd[i] == '=')
		res[idx++] = ft_substr(cmd, i + 1, ft_strlen(cmd) - i);
	res[idx] = 0;
	return (res);
}

static int	export_env(t_data *data, char *cmd)
{
	t_env	*ptr;
	char	**res;

	res = split_cmd(cmd);
	if (res == NULL || validate_name(res[0]))
	{
		free_cmds(res);
		return (1);
	}
	ptr = find_env(&data->env_head, res[0]);
	if (ptr)
	{
		if (res[1])
		{
			free(ptr->value);
			ptr->value = res[1];
		}
		free(res[0]);
	}
	else
		add_to_list(&data->env_head, new_env(res[0], res[1]));
	free(res);
	return (0);
}

static t_env	*new_env(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		handle_error("malloc error");
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}
