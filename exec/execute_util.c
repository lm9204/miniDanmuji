/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:39:13 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/07 15:12:49 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many_pipes(t_list *finder)
{
	int	pipe_cnt;

	pipe_cnt = 0;
	while (finder)
	{
		if (finder->flag == PIPE)
			pipe_cnt++;
		finder = finder->next;
	}
	return (pipe_cnt);
}

t_list *push_list(t_list *finder)
{
	while (finder)
	{
		if (finder->flag == PIPE)
		{
			finder = finder->next;
			break;
		}
		finder = finder->next;
	}
	return (finder);
}
