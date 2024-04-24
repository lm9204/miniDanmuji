/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:02:25 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/24 15:21:47 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_status(t_data *data, int *status)
{
	int	exit_code;

	exit_code = WEXITSTATUS(*status);
	free(data->exit_status);
	data->exit_status = ft_itoa(exit_code);
	return ;
}

void	signal_status(t_data *data, int *status)
{
	if (WTERMSIG(*status) == 2)
	{
		free(data->exit_status);
		data->exit_status = ft_itoa(130);
		printf("\n");
	}
	else if (WTERMSIG(*status) == 3)
	{
		free(data->exit_status);
		data->exit_status = ft_itoa(131);
		printf("Quit: %d\n", 3);
	}
	return ;
}

void	wait_child(int child_cnt, t_data *data)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < child_cnt)
	{
		wait(&status);
		if (WIFEXITED(status))
			exit_status(data, &status);
		else if (WIFSIGNALED(status))
			signal_status(data, &status);
		i++;
	}
}
