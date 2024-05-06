/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:24:19 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/06 14:46:54 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	if (envp == NULL)
		return (NULL);
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
	int	res;

	res = ft_strncmp(cmd, "", 2);
	if (res == 0)
		return (1);
	return (0);
}

int	is_not_command(char *path)
{
	if (path == NULL)
		return (1);
	return (0);
}

int	is_not_existing_file(char *path)
{
	int	res;

	res = access(path, F_OK);
	if (res == -1)
		return (1);
	return (0);
}

void	error_handler(t_cmd *cmd_ary, char *cmd_path, t_fd *backup)
{
	if (is_not_existing_env_variable(cmd_ary->cmds[0]))
		exit(0);
	if (ft_strchr(cmd_ary->cmds[0], '/') != 0)
		check_slash(cmd_path, backup);
	if (is_not_command(cmd_path))
	{
		dup2(backup->std_output, STDOUT_FILENO);
		close(backup->std_output);
		printf("Danmoujishell: %s: command not found\n", cmd_ary->cmds[0]);
		exit(127);
	}
	return ;
}
