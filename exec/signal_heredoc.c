/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:20 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/12 21:37:54 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    handle_sigint_heredoc(int sig)
{
    if (sig == SIGINT)
    {
		write (1, "\n", 1);
		// rl_on_new_line();			//다음에 출력될 문자열은 새로운 줄에서 시작할 거라 알려준다.
		// rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
		// rl_redisplay();         // readline 함수의 인자로 넣은 문자열을 다시 출력한다.
        exit(1);
    }
}

void    signal_handler_heredoc(void)
{
    signal(SIGINT, handle_sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
}
