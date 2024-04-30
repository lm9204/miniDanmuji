/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:24:19 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/30 15:15:20 by seongjko         ###   ########.fr       */
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

int	is_not_existing_env_variable(char *cmd)
{
	return (ft_strncmp(cmd, "", 2));
}

void	error_handler(t_cmd *cmd_ary, char *cmd_path, t_fd *backup)
{
	if (!is_not_existing_env_variable(cmd_ary->cmds[0]))
		exit(0);
	if (is_directory(cmd_path))
	{
		errno = EISDIR;
		dup2(backup->std_output, STDOUT_FILENO);
		printf("Danmoujishell: %s: %s\n", cmd_ary->cmds[0], strerror(errno));
		exit(126);
	}
	if (is_unexecutable_file(cmd_path))
	{
		errno = EACCES;
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("Danmoujishell: %s: %s\n", cmd_ary->cmds[0], strerror(errno));
		exit(126);
	}
	if (is_not_command(cmd_path))
	{
		errno = ENOENT;
		dup2(backup->std_output, STDOUT_FILENO);
		printf("Danmoujishell: %s: command not found\n", cmd_ary->cmds[0]);
		exit(127);
	}
	return ;
}

int	is_not_command(char *path)
{
	if (!access(path, X_OK))
		return (0);
	return (1);
}
