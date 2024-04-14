/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:25:28 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 16:45:01 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int flag)
{
	if (flag == PARENT)
		signal_parent();
	// else if (flag == CHILD)
	// 	signal_child();
	else if (flag == HEREDOC)
		signal_heredoc();
	else if (flag == IGNORE)
	    signal_ignore();
    return ;
}
