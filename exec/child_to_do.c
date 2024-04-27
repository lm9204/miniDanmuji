/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_to_do.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:26:22 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/30 19:36:33 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_to_do(t_list *finder, t_process *process, t_data *data)
{
	t_fd	backup;

	backup.std_input = dup(STDIN_FILENO);
	backup.std_output = dup(STDOUT_FILENO);
	signal_handler(CHILD);
	first_or_middle_or_last_child(process);
	if (!redirec_handler(finder, 0, data))
		exit(1);
	print_list(&finder);
	cmd_handler(finder, data, process, &backup);
	exit(0);
	return ;
}
