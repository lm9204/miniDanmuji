/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:44:33 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/15 02:48:38 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_it_executable(t_cmd *cmd_ary)
{
    if (!ft_strncmp(cmd_ary->cmds[0], "cd", ft_strlen("cd")))
        return (0);
    if (!ft_strncmp(cmd_ary->cmds[0], "export", ft_strlen("export")))
        return (0);
    if (!ft_strncmp(cmd_ary->cmds[0], "unset", ft_strlen("unset")))
        return (0);
    if (!ft_strncmp(cmd_ary->cmds[0], "exit", ft_strlen("exit")))
        return (0);
    return (1);
}

int is_it_builtin(t_cmd *cmd_ary)
{
    if (!ft_strncmp(cmd_ary->cmds[0], "cd", ft_strlen("cd")))
        return (1);
    if (!ft_strncmp(cmd_ary->cmds[0], "export", ft_strlen("export")))
        return (1);
    if (!ft_strncmp(cmd_ary->cmds[0], "unset", ft_strlen("unset")))
        return (1);
    if (!ft_strncmp(cmd_ary->cmds[0], "exit", ft_strlen("exit")))
        return (1);
    if (!ft_strncmp(cmd_ary->cmds[0], "echo", ft_strlen("echo")))
        return (1);
    if (!ft_strncmp(cmd_ary->cmds[0], "pwd", ft_strlen("pwd")))
        return (1);
    if (!ft_strncmp(cmd_ary->cmds[0], "env", ft_strlen("env")))
        return (1);
    return (0);
}

void    execute_directly(t_cmd *cmd_ary, t_env **head)
{
    if (!ft_strncmp(cmd_ary->cmds[0], "cd", ft_strlen("cd")))
        ft_echo(cmd_ary->cmds);
    if (!ft_strncmp(cmd_ary->cmds[0], "export", ft_strlen("export")))
        ft_export(head, cmd_ary->cmds);
    if (!ft_strncmp(cmd_ary->cmds[0], "unset", ft_strlen("unset")))
        ft_unset(head, cmd_ary->cmds);
    if (!ft_strncmp(cmd_ary->cmds[0], "exit", ft_strlen("exit")))
        ft_exit(cmd_ary->cmds[1]);
    if (!ft_strncmp(cmd_ary->cmds[0], "echo", ft_strlen("echo")))
        ft_echo(cmd_ary->cmds);
    if (!ft_strncmp(cmd_ary->cmds[0], "pwd", ft_strlen("pwd")))
        ft_pwd();
    if (!ft_strncmp(cmd_ary->cmds[0], "env", ft_strlen("env")))
        ft_env(head);
    return ;
}

void    check_executable_first(t_cmd *cmd_ary, t_env **head)
{
    if (!is_it_executable(cmd_ary))
        return ;
    if (!ft_strncmp(cmd_ary->cmds[0], "echo", ft_strlen("echo")))
        ft_echo(cmd_ary->cmds);
    if (!ft_strncmp(cmd_ary->cmds[0], "pwd", ft_strlen("pwd")))
        ft_pwd();
    if (!ft_strncmp(cmd_ary->cmds[0], "env", ft_strlen("env")))
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
