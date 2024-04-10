/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pre_handler_util.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:13:35 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/08 13:59:15 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_in_tmp_file(char *res, char *delimeter)
{
	char	*file_path;
	int		tmp_fd;
	
	file_path = ft_strjoin("/Users/seongjko/library/caches/", delimeter);
	tmp_fd = open(file_path, O_WRONLY, 0644);
	if (tmp_fd == -1)
	{
		perror("failed opening file\n");
		exit(1);
	}
	write(tmp_fd, res, ft_strlen(res));
	free(file_path);
	close(tmp_fd);
	return ;
}

void	new_tmp_file(char *delimeter)
{
	int		tmp_fd;
	char	*file_path;

	file_path = ft_strjoin("/Users/seongjko/library/caches/", delimeter);
	tmp_fd = open(file_path, O_CREAT | O_WRONLY, 0644);
	printf("%d\n", tmp_fd);
	if (tmp_fd == -1)
	{
		printf("failed opening tmp file-heredoc\n");
		exit(1);
	}
	free(file_path);
	close(tmp_fd);
	return ;
}

void	create_tmp_files(t_list *finder, int *is_heredoc)
{
	t_redirect	*redirec;

	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)(finder->content);
			if (redirec->type == HEREDOC)
			{
				*is_heredoc = 1;
				new_tmp_file(redirec->file);
				redirec->type = HEREINPUT;
			}
		}
		finder = finder->next;
	}
	return ;
}
