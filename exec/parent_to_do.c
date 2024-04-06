/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_to_do.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:08:30 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/06 19:02:18 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int signal_value;

void    parent_to_do(t_process *process)
{
    if (process->i != 0)
		close(process->temp_fd);
	if (process->i != process->pipe_cnt && process->pipe_cnt != 0)
		process->temp_fd = dup(process->fd[0]);
	close(process->fd[0]);
	close(process->fd[1]);
	wait(process->status);
	kill(0, SIGINT); //현재 프로세스의 프로세스 그룹에 종료하라는 시그널을 보냄
	signal_value = 0; //자식 프로세스의 실행이 종료되었음을 알려줌
    return ;
}
