/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:07:07 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/26 15:26:05 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == name[j])
		{
			if (envp[i][j + 1] == '=')
				return (envp[i] + j + 2);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*find_accessable_path(t_cmd *cmd_ary, char **envp_path)
{
	int		i;
	char	*slash_path;
	char	*cmd_path;

	i = -1;
	while (envp_path[++i])
	{
		slash_path = ft_strjoin(envp_path[i], "/");
		cmd_path = ft_strjoin(slash_path, cmd_ary->cmds[0]);
		if (!access(cmd_path, X_OK))
		{
			free(slash_path);
			return (cmd_path);
		}
		free(slash_path);
		free(cmd_path);
	}
	return (0);
}

char	*assemble_cmd_path(void *cmds, char **envp_path)
{
	t_cmd	*cmd_ary;

	cmd_ary = (t_cmd *)cmds;
	if (ft_strchr(cmd_ary->cmds[0], '/') != 0)
		return (cmd_ary->cmds[0]);
	return (find_accessable_path(cmd_ary, envp_path));
}

void	execute_cmd(t_cmd *cmd_ary, char *cmd_path, t_fd *backup, char **envp)
{
	if (execve(cmd_path, cmd_ary->cmds, envp) == -1)
	{
		dup2(backup->std_output, STDOUT_FILENO);
		printf("Danmoujishell: %s: command not found\n", cmd_ary->cmds[0]);
		exit(127);
	}
}

void	cmd_handler(t_list *finder, t_data *data, t_process *process, \
t_fd *backup)
{
	char	**envp;
	int		check_builtin;

	envp = list_to_envp(&data->env_head);
	while (finder && finder->flag != PIPE)
	{
		check_builtin = is_it_builtin((t_cmd *)finder->content);
		if (finder->flag == CMD && check_builtin == 1)
		{
			exit(builtin_handler((t_cmd *)finder->content, \
			&data->env_head, process, data));
			break ;
		}
		else if (finder->flag == CMD && check_builtin == 0)
		{
			execute_cmd(\
			(t_cmd *)finder->content, \
			assemble_cmd_path(finder->content, data->splitted_exec_path), \
			backup, \
			envp);
			break ;
		}
		finder = finder->next;
	}
	return ;
}
