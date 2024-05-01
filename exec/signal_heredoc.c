/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:20 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/01 19:56:39 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_signal(int flag)
{
	if (flag == SIGINT)
	{
		printf(">                       \n");
		exit(1);
	}
	return ;
}

void	signal_heredoc(void)
{
	signal(SIGINT, heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
	return ;
}
