/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:15:57 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/30 16:15:08 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin_without_pipe(t_list *finder, t_data *data)
{
	t_fd	backup;
	int		exit_num;

	backup.std_input = dup(STDIN_FILENO);
	backup.std_output = dup(STDOUT_FILENO);
	if (!redirec_handler(finder, 1, data))
		return ;
	exit_num = builtin_handler((t_cmd *)finder->content, \
	&data->env_head, data);
	free(data->exit_status);
	data->exit_status = ft_itoa(exit_num);
	dup2(backup.std_input, STDIN_FILENO);
	dup2(backup.std_output, STDOUT_FILENO);
	return ;
}

char	*error_header(char *input)
{
	char	*res;

	res = ft_strjoin("Danmoujishell: ", input);
	return (res);
}

int	pre_processor(t_list *finder, t_data *data)
{
	int	check_builtin;

	heredoc_handler(finder, data);
	if (!how_many_cmds(finder))
	{
		redirec_handler(finder, 2, data);
		unlink_heredoc_files(finder);
		return (0);
	}
	if (!how_many_pipes(finder))
	{
		check_builtin = is_it_builtin((t_cmd *)finder->content);
		if (check_builtin == 0)
			return (0);
		else if (check_builtin == 1)
		{
			handle_builtin_without_pipe(finder, data);
			return (0);
		}
		else if (check_builtin == 2)
			return (1);
	}
	return (1);
}
