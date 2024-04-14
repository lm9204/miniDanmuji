/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:20 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 20:48:38 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    heredoc_handler(int flag)
{
    if (flag == SIGINT)
    {
		write (1, "\n", 1);
        exit(1);
    }
    return ;
}

void    signal_heredoc(void)
{
    signal(SIGINT, heredoc_handler);
    signal(SIGQUIT, SIG_IGN);
    return ;
}
