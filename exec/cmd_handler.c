/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:07:07 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/30 12:27:41 by seongjko         ###   ########.fr       */
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
	// printf("s\n");
	//$[env list에 없는 변수]가 들어왔을 경우
	if (!ft_strncmp(cmd_ary->cmds[0], "", 2))
		exit(0);
	//directory일 경우
	if (is_directory(cmd_path))
	{
		errno = EISDIR;
		dup2(backup->std_output, STDOUT_FILENO);
		printf("Danmoujishell: %s: %s\n", cmd_ary->cmds[0], strerror(errno));
		exit(126);
	}
	//파일이 존재하는데 권한이 없을 경우 -> ./[경로] 이렇게 들어올 경우의 처리
	if (is_unexecutable_file(cmd_path))
	{
		errno = EACCES;
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("Danmoujishell: %s: %s\n", cmd_ary->cmds[0], strerror(errno));
		exit(126);
	}
	//command not found에 해당하는 거 걸러주기 -> [명령어] 이렇게 들어올 경우의 처리
	if (is_not_command(cmd_path))
	{
		errno = ENOENT;
		dup2(backup->std_output, STDOUT_FILENO);
		// printf("Danmoujishell: command not found: %s\n", cmd_path);
		exit(127);
	}
	if (execve(cmd_path, cmd_ary->cmds, envp) == -1)
	{
		// dup2(backup->std_output, STDOUT_FILENO);
		// printf("Danmoujishell: %s: command not found\n", cmd_ary->cmds[0]);
		exit(127);
	}
}

void	cmd_handler(t_list *finder, t_data *data, t_process *process, \
t_fd *backup)
{
	char	**envp;
	int		check_builtin;

	envp = list_to_envp(&data->env_head);
	if (*envp == NULL)
		envp = NULL;
	while (finder && finder->flag != PIPE)
	{
		if (finder->flag == CMD)
			check_builtin = is_it_builtin((t_cmd *)finder->content);
		if (finder->flag == CMD && check_builtin == 1)
		{
			exit(builtin_handler((t_cmd *)finder->content, \
			&data->env_head, process, data));
			break ;
		}
		else if (finder->flag == CMD && check_builtin == 2)
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
