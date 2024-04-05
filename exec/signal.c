/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:48:45 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/05 21:07:19 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ctrl + C
void	handle_sigint(int sig) {
	if (sig == SIGINT)
	{
		// write(1, "hello world\n", 11);
		write (1, "\n", 1);
		rl_on_new_line();			//다음에 출력될 문자열은 새로운 줄에서 시작할 거라 알려준다.
		rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
		rl_redisplay();         // 가장 최근에 콘솔에 출력된 문자열을 다시 출력한다.
	}
	return ;
}

//ctrl + backslash

//ctrl + D
void	handle_sigterm(int sig) {
	if (sig == SIGTERM)
	{
		rl_on_new_line();			//다음에 출력될 문자열은 새로운 줄에서 시작할 거라 알려준다.
		rl_redisplay();
		exit(1);
	}
	return ;
}

void	signal_handler(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handle_sigterm);
}
