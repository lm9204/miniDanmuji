/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:15:57 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/23 15:36:28 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin_without_pipe(t_list *finder, t_data *data, \
t_process *process)
{
	if (!redirec_handler(finder, 1))
		return ;
	builtin_handler((t_cmd *)finder->content, \
	&data->env_head, process, data);
	return ;
}

char	*error_header(char *input)
{
	char	*res;

	res = ft_strjoin("Danmoujishell: ", input);
	return (res);
}

int	pre_processor(t_list *finder, t_data *data, t_process *process)
{
	if (!heredoc_handler(finder, data))
		return (0);
	if (!how_many_cmds(finder))
	{
		unlink_heredoc_files(finder);
		return (0);
	}
	if (!how_many_pipes(finder) && is_it_builtin((t_cmd *)finder->content))
	{
		handle_builtin_without_pipe(finder, data, process);
		return (0);
	}
	return (1);
}
