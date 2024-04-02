/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:26:47 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/01 13:29:57 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_child(t_process *process)
{
	int	i;

	i = 0;
	process->status = NULL;
	while (i < process->pipe_cnt)
	{
		wait(process->status);
		i++;
	}
}