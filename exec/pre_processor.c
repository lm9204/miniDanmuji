/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:15:57 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/21 11:48:52 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin_without_pipe(t_list *finder, t_data *data, \
t_process *process)
{
	t_fd	backup;

	backup.std_output = dup(STDOUT_FILENO);
	if (!redirec_handler(finder))
	{
		dup2(backup.std_input, STDIN_FILENO);
		dup2(backup.std_output, STDOUT_FILENO);
		close(backup.std_input);
		close(backup.std_output);
		return ;
	}
	builtin_handler((t_cmd *)finder->content, \
	&data->env_head, process, data);
	dup2(backup.std_input, STDIN_FILENO);
	dup2(backup.std_output, STDOUT_FILENO);
	close(backup.std_input);
	close(backup.std_output);
}

char	*error_header(char *input)
{
	char	*input_with_colon;
	char	*temp;
	char	*res;

	input_with_colon = ft_strjoin(input, ":");
	temp = input_with_colon;
	res = ft_strjoin("Danmoujishell: ", input_with_colon);
	free(temp);
	return (res);
}

int	pre_processor(t_list *finder, t_data *data, t_process *process)
{
	heredoc_handler(finder, data);
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
