/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:48:45 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 16:52:44 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay(); 
	}
	else if (sig == SIGQUIT)
		exit(1);
	return ;
}

void	signal_parent(void)
{
	signal(SIGINT, parent_handler);
	signal(SIGTERM, parent_handler);
	signal(SIGQUIT, SIG_IGN);
	return ;
}
