/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:43:43 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/16 20:57:02 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_main(t_list **head, t_data *data)
{
	t_list		*finder;
	t_list		*first;
	t_process	process;
	int			i;
	
	finder = *head;
	first = *head;
	process.pipe_cnt = how_many_pipes(finder);
	process.status = NULL;
	if (!pre_processor(finder, data, &process))
	{
		printf("no fork\n");
		return (0);
	}
	i = -1;
	while (++i < process.pipe_cnt + 1)		// pipe의 갯수 + 1만큼 fork를 떠야 하므로 +1
	{
		if (i != 0) 						//파이프 바로 뒤까지 linked list 밀어주기
			finder = push_list_to_back(finder);
		process.i = i; 						//자식 프로세스별로 넘버링 부여
		if (pipe(process.fd) == -1)			//파이프 생성
		{
			perror("failed opening pipe\n");
			exit(1);
		}
		signal_handler(IGNORE);
		process.pid = fork();				//포크
		if (process.pid == -1)
		{
			perror("failed fork\n");
			exit(1);
		}
		else if (process.pid == 0)     	   //자식
			child_to_do(finder, &process, data);
		else                    			//부모
			parent_to_do(&process);
	}
	wait_child(process.pipe_cnt + 1, data);
	signal_handler(PARENT);
    return (1);
}
