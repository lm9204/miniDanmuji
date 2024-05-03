/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:32:52 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/03 17:12:36 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(t_redirect *redirec)
{
	if (redirec->type == 4)
		return (open(redirec->new_file_path, O_RDONLY, 0644));
	else
		return (open(redirec->file, O_RDONLY, 0644));
	return (0);
}

int	redirect_input(t_list *finder, int flag, t_data *data)
{
	int			file_fd;
	t_redirect	*redirec;
	char		*error_msg;

	redirec = (t_redirect *)(finder->content);
	file_fd = open_file(redirec);
	if (file_fd == -1)
	{
		free(data->exit_status);
		data->exit_status = ft_itoa(1);
		error_msg = error_header(redirec->file);
		perror(error_msg);
		free(error_msg);
		return (0);
	}
	if (flag == CMD_REDIREC)
		dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return (1);
}

int	redirect_output(t_list *finder, int flag, t_data *data)
{
	int			file_fd;
	t_redirect	*redirec;
	char		*error_msg;

	redirec = (t_redirect *)(finder->content);
	file_fd = open(redirec->file, O_RDWR | O_CREAT, 0644);
	if (file_fd == -1)
	{
		free(data->exit_status);
		data->exit_status = ft_itoa(1);
		error_msg = error_header(redirec->file);
		perror(error_msg);
		free(error_msg);
		return (0);
	}
	if (flag != REDIREC_ALONE)
		dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (1);
}

int	redirect_output_append(t_list *finder, int flag, t_data *data)
{
	int			file_fd;
	t_redirect	*redirec;
	char		*error_msg;

	redirec = (t_redirect *)(finder->content);
	file_fd = open(redirec->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
	{
		free(data->exit_status);
		data->exit_status = ft_itoa(1);
		error_msg = error_header(redirec->file);
		perror(error_msg);
		free(error_msg);
		return (0);
	}
	if (flag != REDIREC_ALONE)
		dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (1);
}

// [<<] = 0  [>>] = 1  [<] = 2  [>] = 3  [<< -> <] = 4
int	redirec_handler(t_list *finder, int flag, t_data *data)
{
	t_redirect	*redirec;
	char		*tmp;
	int			error_flag;

	error_flag = 1;
	while (finder && finder->flag != PIPE)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)(finder->content);
			tmp = redirec->file;
			redirec->file = checkcmd(data, redirec->file, 0);
			free(tmp);
			if (redirec->type == APPEND)
				error_flag = redirect_output_append(finder, flag, data);
			if (redirec->type == INPUT || redirec->type == HEREINPUT)
				error_flag = redirect_input(finder, flag, data);
			if (redirec->type == OUTPUT)
				error_flag = redirect_output(finder, flag, data);
			if (!error_flag)
				return (error_flag);
		}
		finder = finder->next;
	}
	return (error_flag);
}
