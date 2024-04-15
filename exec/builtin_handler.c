/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:44:33 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/15 19:15:35 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_it_executable(t_cmd *cmd_ary)
{
    if (!ft_strncmp(cmd_ary->cmds[0], "cd", ft_strlen("cd") + 1))
        return (0);
    if (!ft_strncmp(cmd_ary->cmds[0], "export", ft_strlen("export") + 1))
        return (0);
    if (!ft_strncmp(cmd_ary->cmds[0], "unset", ft_strlen("unset") + 1))
        return (0);
    if (!ft_strncmp(cmd_ary->cmds[0], "exit", ft_strlen("exit") + 1))
        return (0);
    return (1);
}

int is_it_builtin(t_cmd *cmd_ary)
{
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
    return (0);
}

void    execute_directly(t_cmd *cmd_ary, t_env **head)
{
    if (!ft_strncmp(cmd_ary->cmds[0], "cd", ft_strlen("cd") + 1))
        ft_cd(head, cmd_ary->cmds[1]);
    if (!ft_strncmp(cmd_ary->cmds[0], "export", ft_strlen("export") + 1))
        ft_export(head, cmd_ary->cmds);
    if (!ft_strncmp(cmd_ary->cmds[0], "unset", ft_strlen("unset") + 1))
        ft_unset(head, cmd_ary->cmds);
    if (!ft_strncmp(cmd_ary->cmds[0], "exit", ft_strlen("exit") + 1))
        ft_exit(cmd_ary->cmds[1]);
    if (!ft_strncmp(cmd_ary->cmds[0], "echo", ft_strlen("echo") + 1))
        ft_echo(cmd_ary->cmds);
    if (!ft_strncmp(cmd_ary->cmds[0], "pwd", ft_strlen("pwd") + 1))
        ft_pwd();
    if (!ft_strncmp(cmd_ary->cmds[0], "env", ft_strlen("env") + 1))
        ft_env(head);
    return ;
}

void    check_executable_first(t_cmd *cmd_ary, t_env **head)
{
    if (!is_it_executable(cmd_ary))
        return ;
    if (!ft_strncmp(cmd_ary->cmds[0], "echo", ft_strlen("echo") + 1))
        ft_echo(cmd_ary->cmds);
    if (!ft_strncmp(cmd_ary->cmds[0], "pwd", ft_strlen("pwd") + 1))
        ft_pwd();
    if (!ft_strncmp(cmd_ary->cmds[0], "env", ft_strlen("env") + 1))
        ft_env(head);
    
}

void    builtin_handler(t_cmd *cmd_ary, t_env **head, t_process *process)
{
    if (!process->pipe_cnt)
        execute_directly(cmd_ary, head);
    else
        check_executable_first(cmd_ary, head);
    return ;
}
