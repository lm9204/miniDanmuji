/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:07:07 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/06 14:48:14 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_accessable_path(t_cmd *cmd_ary, char **envp_path)
{
	int		i;
	char	*slash_path;
	char	*cmd_path;

	i = -1;
	if (envp_path == NULL)
		return (NULL);
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
	return (NULL);
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
	error_handler(cmd_ary, cmd_path, backup);
	if (execve(cmd_path, cmd_ary->cmds, envp) == -1)
	{
		dup2(backup->std_output, STDOUT_FILENO);
		close(backup->std_output);
		printf("Danmoujishell: %s: execve failed\n", cmd_ary->cmds[0]);
		exit(127);
	}
}

void	reset_splitted_exec_path(t_data *data, char **envp)
{
	char	*envp_path;

	free(data->splitted_exec_path);
	envp_path = ft_getenv("PATH", envp);
	if (envp_path == NULL)
		data->splitted_exec_path = NULL;
	else
		data->splitted_exec_path = ft_split(envp_path, ':');
	return ;
}

void	cmd_handler(t_list *finder, t_data *data, t_fd *backup)
{
	char	**envp;
	int		check_builtin;

	envp = list_to_envp(&data->env_head);
	if (*envp == NULL)
		envp = NULL;
	reset_splitted_exec_path(data, envp);
	while (finder && finder->flag != PIPE)
	{
		is_this_builtin(&check_builtin, finder);
		if (finder->flag == CMD && check_builtin == 1)
		{
			exit(builtin_handler((t_cmd *)finder->content, \
			&data->env_head, data));
			break ;
		}
		else if (finder->flag == CMD && check_builtin == 2)
		{
			execute_cmd((t_cmd *)finder->content, \
			assemble_cmd_path(finder->content, data->splitted_exec_path), \
			backup, envp);
			break ;
		}
		finder = finder->next;
	}
}
