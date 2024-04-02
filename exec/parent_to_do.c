/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_to_do.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:08:30 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/01 15:20:05 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    parent_to_do(t_process *process)
{
    if (process->i != 0)
		close(process->temp_fd);
	if (process->i != process->pipe_cnt)
		process->temp_fd = dup(process->fd[0]);
	close(process->fd[0]);
	close(process->fd[1]);
    return ;
}