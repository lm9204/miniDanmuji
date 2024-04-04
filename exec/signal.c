/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:48:45 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/04 15:32:32 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ctrl + C
void	handle_sigint(int sig) {
	if (sig != SIGINT)
		return ;
	else
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	return ;
}

//ctrl + backslash
void	handle_sigquit(int sig) {
	if (sig == SIGQUIT)
	{
		
	}
	return ;
}

//ctrl + D
void	handle_sigterm(int sig) {
	//ctrl + D는 main문에서 canonical -> uncanonical로 
	//변경해줘야 함
	//끝난 거 아님
	if (sig == SIGTERM)
		exit(1);
	return ;
}

void	signal_handler(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGTERM, handle_sigterm);
}
