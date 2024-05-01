/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:25:28 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/01 19:55:43 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int flag)
{
	if (flag == PARENT)
		signal_parent();
	else if (flag == CHILD)
		signal_child();
	else if (flag == HEREDOC)
		signal_heredoc();
	else if (flag == IGNORE)
		signal_ignore();
	return ;
}

void	sigterm_handler(char *nl, int flag)
{
	if (flag == HEREDOC)
	{
		if (nl == NULL)
			exit(0);
	}
	if (flag == PARENT)
	{
		if (nl == NULL)
		{
			printf("\001\0338\002exit\n");
			exit(0);
		}
	}
}
