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
	signal_handler(CHILD);
	first_or_middle_or_last_child(process);
	redirec_handler(finder);
	cmd_handler(finder, data, process);
	exit(0);
	return ;
}
