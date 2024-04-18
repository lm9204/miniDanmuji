/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:42:42 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/19 03:28:48 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGINT)
		exit(1);
	else if (sig == SIGTERM)
		exit(1);
	return ;
}

void	signal_child(void)
{
	signal(SIGINT, child_handler);
	signal(SIGTERM, child_handler);
	signal(SIGQUIT, SIG_IGN);
	return ;
}
