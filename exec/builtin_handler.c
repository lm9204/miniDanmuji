/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:44:33 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/05 19:21:54 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_it_builtin(t_cmd *cmd_ary)
{
	if (cmd_ary == NULL || cmd_ary->cmds[0] == NULL)
		return (0);
	if (!ft_strncmp(cmd_ary->cmds[0], "cd", ft_strlen("cd") + 1))
		return (1);
	if (!ft_strncmp(cmd_ary->cmds[0], "export", ft_strlen("export") + 1))
		return (1);
	if (!ft_strncmp(cmd_ary->cmds[0], "unset", ft_strlen("unset") + 1))
		return (1);
	if (!ft_strncmp(cmd_ary->cmds[0], "exit", ft_strlen("exit") + 1))
		return (1);
	if (!ft_strncmp(cmd_ary->cmds[0], "echo", ft_strlen("echo") + 1))
		return (1);
	if (!ft_strncmp(cmd_ary->cmds[0], "pwd", ft_strlen("pwd") + 1))
		return (1);
	if (!ft_strncmp(cmd_ary->cmds[0], "env", ft_strlen("env") + 1))
		return (1);
	return (2);
}

int	builtin_handler(t_cmd *cmd_ary, t_env **head, t_data *data)
{
	if (!ft_strncmp(cmd_ary->cmds[0], "cd", ft_strlen("cd") + 1))
		return (ft_cd(data, &cmd_ary->cmds[1]));
	if (!ft_strncmp(cmd_ary->cmds[0], "export", ft_strlen("export") + 1))
		return (ft_export(data, cmd_ary->cmds));
	if (!ft_strncmp(cmd_ary->cmds[0], "unset", ft_strlen("unset") + 1))
		return (ft_unset(head, cmd_ary->cmds));
	if (!ft_strncmp(cmd_ary->cmds[0], "exit", ft_strlen("exit") + 1))
		return (ft_exit(&cmd_ary->cmds[1]));
	if (!ft_strncmp(cmd_ary->cmds[0], "echo", ft_strlen("echo") + 1))
		return (ft_echo(cmd_ary->cmds));
	if (!ft_strncmp(cmd_ary->cmds[0], "pwd", ft_strlen("pwd") + 1))
		return (ft_pwd(data->pwd));
	if (!ft_strncmp(cmd_ary->cmds[0], "env", ft_strlen("env") + 1))
		return (ft_env(head));
	return (0);
}
