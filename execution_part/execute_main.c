/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:43:43 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/30 20:51:04 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_main(t_list **head)
{
	t_list	*finder;
	// int		fd[2];
	// int		i;
	// int		pipe_cnt;
	// pid_t	pid;
	
	finder = *head;
	heredoc_pre_handler(finder);

	print_list(&finder);
	// pipe_cnt = how_many_pipes(finder);
	// i = -1;
	// while (++i < pipe_cnt + 1) // pipe의 갯수 + 1만큼 fork를 떠야 하므로 +1
	// {
	// 	//파이프 바로 뒤까지 linked list 밀어주기
	// 	if (i != 0)
	// 		finder = push_list(finder);
	// 	//파이프 생성
	// 	if (pipe(fd) == -1)
	// 	{
	// 		perror("failed opening pipe\n");
	// 		exit(1);
	// 	}
	// 	//포크
	// 	pid = fork();
	// 	if (pid == -1)             //에러처리
	// 	{
	// 		perror("failed fork\n");
	// 		exit(1);
	// 	}
	// 	else if (pid == 0)        //자식
	// 		child_to_do(finder, fd);
	// 	else                      //부모
	// 		parent_to_do(finder, fd);
	// }
    return (1);
}
