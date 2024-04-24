/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:42:42 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/24 15:07:49 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void child_handler(int sig)
{
	(void)sig;
	return ;
}

void signal_child(void)
{
    struct sigaction act;

    act.sa_handler = child_handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
    // signal(SIGINT, child_handler);
	// signal(SIGQUIT, SIG_IGN);

    return;
}