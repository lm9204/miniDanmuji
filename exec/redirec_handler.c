/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:32:52 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/24 12:34:28 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(t_redirect *redirec)
{
	char	*path;

	if (redirec->type == 4)
		path = redirec->new_file_path;
	else
		path = redirec->file;
	return (open(path, O_RDONLY, 0644));
}

int	redirect_input(t_list *finder, int builtin)
{
	int			file_fd;
	t_redirect	*redirec;
	char		*error_msg;

	redirec = (t_redirect *)(finder->content);
	file_fd = open_file(redirec);
	if (file_fd == -1)
	{
		error_msg = error_header(redirec->file);
		perror(error_msg);
		return (0);
	}
	if (builtin != 1)
		dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return (1);
}

int	redirect_output(t_list *finder)
{
	int			file_fd;
	t_redirect	*redirec;
	char		*error_msg;

	redirec = (t_redirect *)(finder->content);
	file_fd = open(redirec->file, O_RDWR | O_CREAT, 0644);
	if (file_fd == -1)
	{
		error_msg = error_header(redirec->file);
		perror(error_msg);
		return (0);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (1);
}

int	redirect_output_append(t_list *finder)
{
	int			file_fd;
	t_redirect	*redirec;
	char		*error_msg;

	redirec = (t_redirect *)(finder->content);
	file_fd = open(redirec->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
	{
		error_msg = error_header(redirec->file);
		perror(error_msg);
		return (0);
	}
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (1);
}

int	redirec_handler(t_list *finder, int builtin)
{
	t_redirect	*redirec;
	int			flag;

	flag = 1;
	while (finder && finder->flag != PIPE)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)(finder->content);
			if (redirec->type == 1)
				flag = redirect_output_append(finder);
			if (redirec->type == 2 || redirec->type == 4)
				flag = redirect_input(finder, builtin);
			if (redirec->type == 3)
				flag = redirect_output(finder);
			if (flag == 0)
				return (flag);
		}
		finder = finder->next;
	}
	return (flag);
}
