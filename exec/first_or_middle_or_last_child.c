/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_or_middle_or_last_child.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:09:37 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/19 03:23:15 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_child_process(int read_end, int write_end, int pipe_cnt)
{
	close(read_end);
	if (pipe_cnt != 0)
		dup2(write_end, STDOUT_FILENO);
	close(write_end);
	return ;
}

void	middle_child_process(int temp_fd, int read_end, int write_end)
{
	close(read_end);
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
	dup2(write_end, STDOUT_FILENO);
	close(write_end);
	return ;
}

void	last_child_process(int temp_fd, int read_end, int write_end)
{
	close(read_end);
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
	close(write_end);
	return ;
}

void	first_or_middle_or_last_child(t_process *process)
{
	if (process->i == 0)
		first_child_process(process->fd[0], process->fd[1], process->pipe_cnt);
	else if (process->i > 0 && process->i < process->pipe_cnt)
	{
		middle_child_process(process->temp_fd, process->fd[0], \
		process->fd[1]);
	}
	else
	{
		last_child_process(process->temp_fd, process->fd[0], \
		process->fd[1]);
	}
	return ;
}
