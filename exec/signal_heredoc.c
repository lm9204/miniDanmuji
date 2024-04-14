/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:20 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 18:16:39 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    heredoc_handler(int flag)
{
    if (flag == SIGINT)
    {
		write (1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay(); 
        exit(1);
    }
    else if (flag == SIGQUIT)
    {
        rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
        exit(1);
    }
    return ;
}

void    signal_heredoc(void)
{
    signal(SIGINT, heredoc_handler);
    signal(SIGTERM, heredoc_handler);
    signal(SIGQUIT, SIG_IGN);
    return ;
}
