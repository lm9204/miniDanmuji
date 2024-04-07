/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:43:43 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/07 17:04:54 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int signal_value;

int	execute_main(t_list **head, t_data *env)
{
	t_list		*finder;
	t_process	process;
	int			i;
	
	finder = *head;
	heredoc_pre_handler(finder);
	if (!how_many_cmds(finder))
		return (0);
	printf("how_many_cmds: %d\n", how_many_cmds(finder));
	process.pipe_cnt = how_many_pipes(finder);
	process.status = NULL;
	i = -1;
	signal_value = 1;                                                                
	while (++i < process.pipe_cnt + 1)		// pipe의 갯수 + 1만큼 fork를 떠야 하므로 +1
	{
		if (i != 0) 						//파이프 바로 뒤까지 linked list 밀어주기
			finder = push_list(finder);
		process.i = i; 						//자식 프로세스별로 넘버링 부여
		if (pipe(process.fd) == -1)			//파이프 생성
		{
			perror("failed opening pipe\n");
			exit(1);
		}
		process.pid = fork();				//포크
		if (process.pid == -1)
		{
			perror("failed fork\n");
			exit(1);
		}
		else if (process.pid == 0)     	   //자식
			child_to_do(finder, &process, env);
		else                    			//부모
			parent_to_do(&process);
	}
	wait_child(process.pipe_cnt + 1);
	signal_value = 0;
    return (1);
}
