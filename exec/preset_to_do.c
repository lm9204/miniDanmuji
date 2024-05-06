/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset_to_do.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:15:57 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/05 19:25:42 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin_without_pipe(t_list *finder, t_data *data)
{
	t_fd	backup;
	int		exit_num;

	backup.std_input = dup(STDIN_FILENO);
	backup.std_output = dup(STDOUT_FILENO);
	if (!redirec_handler(finder, BUILTIN_REDIREC, data))
	{
		handle_fd_and_exit(data, &backup, 1);
		return ;
	}
	exit_num = builtin_handler((t_cmd *)finder->content, \
	&data->env_head, data);
	handle_fd_and_exit(data, &backup, exit_num);
	return ;
}

char	*error_header(char *input)
{
	char	*res;

	res = ft_strjoin(PROMPT_MSG, input);
	return (res);
}

int	builtin_to_do_by_case(t_list *finder, t_data *data)
{
	int	check_builtin;

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
	return (1);
}

int	preset_to_do(t_list *finder, t_data *data)
{
	heredoc_handler(finder, data);
	if (!how_many_cmds(finder))
	{
		if (!redirec_handler(finder, REDIREC_ALONE, data))
		{
			free(data->exit_status);
			data->exit_status = ft_itoa(1);
			return (0);
		}
		else
			return (0);
	}
	if (!how_many_pipes(finder))
		return (builtin_to_do_by_case(finder, data));
	return (1);
}
