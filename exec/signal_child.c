/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:42:42 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 16:41:46 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ctrl + C
// void	handle_sigint_child(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		// printf("hello world\n");
// 		// write (1, "\n", 1);
// 		// rl_on_new_line();			//다음에 출력될 문자열은 새로운 줄에서 시작할 거라 알려준다.
// 		// rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
// 		// rl_redisplay();         // readline 함수의 인자로 넣은 문자열을 다시 출력한다.
//         exit(1);
// 	}
// 	return ;
// }

// //ctrl + D
// void	handle_sigterm_child(int sig)
// {
// 	if (sig == SIGTERM)
// 	{
// 		rl_on_new_line();			//다음에 출력될 문자열은 새로운 줄에서 시작할 거라 알려준다.
// 		rl_redisplay();
// 		exit(1);
// 	}
// 	return ;
// }

// void    signal_handler_child(void)
// {
//     signal(SIGINT, handle_sigint_child);
// 	signal(SIGQUIT, SIG_IGN);
// 	// signal(SIGTERM, handle_sigterm_child);
//     return ;
// }
