/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:48:45 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/03 21:14:00 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		global_signal_flag = SIGINT;
	}
	return ;
}

void	signal_parent(void)
{
	signal(SIGINT, parent_handler);
	signal(SIGQUIT, SIG_IGN);
	
	while (1)
	{
		if (global_signal_flag == SIGINT)
			ft_putstr_fd("here", 1);
	}

}
