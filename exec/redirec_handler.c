/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:32:52 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/19 05:03:57 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_input(t_list *finder)
{
	int			file_fd;
	t_redirect	*redirec;

	redirec = (t_redirect *)(finder->content);
	if (redirec->type == 4)
		file_fd = open(redirec->new_file_path, \
		O_RDONLY | O_CREAT, 0644);
	else
		file_fd = open(redirec->file, O_RDONLY, 0644);
	if (file_fd == -1)
	{
		printf("Danmoujishell: %s: No such file or directory\n", \
		redirec->file);
		exit(1);
	}
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return ;
}

void	redirect_output(t_list *finder)
{
	int			file_fd;
	t_redirect	*redirec;

	redirec = (t_redirect *)(finder->content);
	file_fd = open(redirec->file, O_RDWR | O_CREAT, 0644);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return ;
}

void	redirect_output_append(t_list *finder)
{
	int			file_fd;
	t_redirect	*redirec;

	redirec = (t_redirect *)(finder->content);
	file_fd = open(redirec->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return ;
}

void	redirec_handler(t_list *finder)
{
	t_redirect	*redirec;

	while (finder && finder->flag != PIPE)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)(finder->content);
			if (redirec->type == 1)
				redirect_output_append(finder);
			else if (redirec->type == 2 || redirec->type == 4)
				redirect_input(finder);
			else if (redirec->type == 3)
				redirect_output(finder);
		}
		finder = finder->next;
	}
	return ;
}
