/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:39:13 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/19 03:23:04 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many_cmds(t_list *finder)
{
	int		cmd_cnt;

	cmd_cnt = 0;
	while (finder)
	{
		if (finder->flag == CMD)
			cmd_cnt++;
		finder = finder->next;
	}
	return (cmd_cnt);
}

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

t_list	*push_list_to_back(t_list *finder)
{
	while (finder)
	{
		if (finder->flag == PIPE)
		{
			finder = finder->next;
			break ;
		}
		finder = finder->next;
	}
	return (finder);
}
