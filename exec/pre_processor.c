/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:15:57 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/19 04:42:19 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin_without_pipe(t_list *finder, t_data *data, \
t_process *process)
{
	int backup_stdin;
	int	backup_stdout;

	backup_stdin = dup(STDIN_FILENO);
    backup_stdout = dup(STDOUT_FILENO);
	redirec_handler(finder);
	builtin_handler((t_cmd *)finder->content, \
	&data->env_head, process, data);
	dup2(backup_stdin, STDIN_FILENO);
    dup2(backup_stdout, STDOUT_FILENO);
    close(backup_stdin);
    close(backup_stdout);
}

int	pre_processor(t_list *finder, t_data *data, t_process *process)
{
	heredoc_handler(finder, data);
	if (!how_many_cmds(finder))
	{
		//delete_heredoc_files.
		return (0);
	}
	if (!how_many_pipes(finder) && is_it_builtin((t_cmd *)finder->content))
	{
		handle_builtin_without_pipe(finder, data, process);
		return (0);
	}
	return (1);
}
