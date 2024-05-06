/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_handler_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:21:14 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/06 14:13:23 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	which_redirect_has_come_in(t_list *finder, int flag, t_data *data, \
int *error_flag)
{
	t_redirect	*redirec;

	redirec = (t_redirect *)(finder->content);
	if (redirec->type == APPEND)
		*error_flag = redirect_output_append(finder, flag, data);
	if (redirec->type == INPUT || redirec->type == HEREINPUT)
		*error_flag = redirect_input(finder, flag, data);
	if (redirec->type == OUTPUT)
		*error_flag = redirect_output(finder, flag, data);
	return ;
}

void	check_redirec_file(t_list *finder, t_data *data)
{
	t_redirect	*redirec;
	char		*tmp;

	redirec = (t_redirect *)(finder->content);
	tmp = redirec->file;
	if (redirec->type == HEREINPUT)
		redirec->file = checkcmd(data, redirec->file, 0);
	else
		redirec->file = parse_redir(data, redirec->file, \
		&data->checkcmd_flag);
	free(tmp);
	return ;
}

void	handle_fd_and_exit(t_data *data, t_fd *backup, int exit_num)
{
	free(data->exit_status);
	data->exit_status = ft_itoa(exit_num);
	dup2(backup->std_input, STDIN_FILENO);
	close(backup->std_input);
	dup2(backup->std_output, STDOUT_FILENO);
	close(backup->std_output);
	return ;
}
