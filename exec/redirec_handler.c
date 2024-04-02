/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:32:52 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/01 15:00:08 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// <<  >>  <  >
// 0   1   2  3
#include "../minishell.h"

void	redirect_input(t_list *finder)
{
	int			file_fd;
	t_redirect	*redirec;
	char		*file_path;

	redirec = (t_redirect *)(finder->content);
	file_path = ft_strjoin("/Users/seongjko/library/caches/", redirec->file);
	file_fd = open(file_path, O_RDONLY, 0644);
	if (file_fd == -1)
	{
		printf("Danmoujishell: %s: No such file or directory", redirec->file);
		exit(1);
	}
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return ;
}

void	redirect_output(t_list *finder)
{
	int file_fd;
	t_redirect *redirec;

	redirec = (t_redirect *)(finder->content);
	file_fd = open(redirec->file, O_RDONLY | O_CREAT, 0644);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return ;
}

void	redirect_output_append(t_list *finder)
{
	int file_fd;
	t_redirect *redirec;

	redirec = (t_redirect *)(finder->content);
	file_fd = open(redirec->file, O_RDONLY | O_CREAT | O_APPEND, 0644);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return ;
}

void	redirec_handler(t_list *finder)
{
	t_redirect	*redirec;
	
	while (finder && finder->flag != 1)
	{
		if (finder->flag == 2)
		{
			redirec = (t_redirect *)(finder->content);
			if (redirec->type == 1)
				redirect_output_append(finder);
			else if (redirec->type == 2)
				redirect_input(finder);
			else if (redirec->type == 3)
				redirect_output(finder);
		}
		finder = finder->next;
	}
	return ;
}


