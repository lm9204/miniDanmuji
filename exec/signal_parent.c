/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:48:45 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/08 13:50:10 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int signal_value;

//ctrl + C
void	handle_sigint(int sig) {
	//자식 프로세스가 실행 중일 때는 시그널 무시
	if (sig == SIGINT && signal_value == 1)
		return ;
	//자식 프로세스가 실행 중이 아닐 때는 시그널 동작
	else if (sig == SIGINT && signal_value == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();			//다음에 출력될 문자열은 새로운 줄에서 시작할 거라 알려준다.
		rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
		rl_redisplay();         // readline 함수의 인자로 넣은 문자열을 다시 출력한다.
	}
	return ;
}

//ctrl + D
void	handle_sigterm(int sig) {
	if (sig == SIGTERM)
	{
		rl_on_new_line();
		rl_redisplay();
		exit(1);
	}
	return ;
}

void	signal_handler_parent(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handle_sigterm);
}
