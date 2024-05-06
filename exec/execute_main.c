/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:43:43 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/06 14:34:22 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	preset(t_process *process, t_data *data, t_list *finder, int *i)
{
	*i = -1;
	process->pipe_cnt = how_many_pipes(finder);
	process->status = NULL;
	if (!preset_to_do(finder, data))
	{
		unlink_heredoc_files(finder);
		return (0);
	}
	return (1);
}

void	afterset(t_process *process, t_data *data, t_list *finder)
{
	wait_child(process->pipe_cnt + 1, data);
	signal_handler(PARENT);
	unlink_heredoc_files(finder);
	return ;
}

void	process_manager(t_process *process, t_data *data, t_list *finder)
{
	if (process->pid == -1)
	{
		perror("failed fork\n");
		exit(1);
	}
	else if (process->pid == 0)
		child_to_do(finder, process, data);
	else
		parent_to_do(process);
	return ;
}

int	execute_main(t_list **head, t_data *data)
{
	t_list		*finder;
	t_process	process;
	int			i;

	finder = *head;
	if (!preset(&process, data, finder, &i))
		return (0);
	while (++i < process.pipe_cnt + 1)
	{
		if (i != 0)
			finder = push_list_to_back(finder);
		process.i = i;
		if (pipe(process.fd) == -1)
		{
			perror("failed opening pipe\n");
			exit(1);
		}
		signal_handler(IGNORE);
		process.pid = fork();
		process_manager(&process, data, finder);
	}
	afterset(&process, data, finder);
	return (1);
}
