/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_to_do.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:26:22 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/30 19:36:33 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_to_do(t_list *finder, t_process *process, t_data *data)
{
	t_fd	backup;

	backup.std_output = dup(STDOUT_FILENO);
	signal_handler(CHILD);
	first_or_middle_or_last_child(process);
	if (!redirec_handler(finder, CMD_REDIREC, data))
	{
		free(data->exit_status);
		data->exit_status = ft_itoa(1);
		close(backup.std_output);
		exit(1);
	}
	cmd_handler(finder, data, &backup);
	close(backup.std_output);
	exit(0);
	return ;
}

void	check_slash(char *cmd_path, t_fd *backup)
{
	if (is_directory(cmd_path))
	{
		errno = EISDIR;
		dup2(backup->std_output, STDOUT_FILENO);
		close(backup->std_output);
		printf("Danmoujishell: %s: %s\n", cmd_path, strerror(errno));
		exit(126);
	}
	if (is_not_existing_file(cmd_path))
	{
		errno = ENOENT;
		dup2(backup->std_output, STDOUT_FILENO);
		close(backup->std_output);
		printf("Danmoujishell: %s: %s\n", cmd_path, strerror(errno));
		exit(127);
	}
	if (is_unexecutable_file(cmd_path))
	{
		errno = EACCES;
		dup2(STDERR_FILENO, STDOUT_FILENO);
		close(backup->std_output);
		printf("Danmoujishell: %s: %s\n", cmd_path, strerror(errno));
		exit(126);
	}
}
