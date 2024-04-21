/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:42:42 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/21 16:48:02 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void child_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "\\Quit: 3\n", 9);
		exit(1);
	}
	return ;
}

void	signal_child(void)
{
	struct sigaction act_int;
	struct sigaction act_quit;

    act_int.sa_handler = child_handler;
    sigemptyset(&act_int.sa_mask);
	sigaddset(&act_int.sa_mask, SIGINT);
    act_int.sa_flags = 0;
    sigaction(SIGINT, &act_int, NULL);
    act_quit.sa_handler = child_handler;
    sigemptyset(&act_quit.sa_mask);
    act_quit.sa_flags = 0;
    sigaction(SIGQUIT, &act_quit, NULL);
	return ;
}
