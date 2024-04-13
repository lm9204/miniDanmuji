/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pre_handler_util.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:13:35 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/12 17:23:33 by seongjko         ###   ########.fr       */
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

void	new_tmp_file(char *delimeter, int i)
{
	int		tmp_fd;
	char	*file_path;
	char	*new_file_name;
	char	*file_number;

	file_number = ft_itoa(i);
	new_file_name = ft_strjoin(delimeter, file_number);
	printf("heredoc_file: %s\n", new_file_name);
	file_path = ft_strjoin("/Users/seongjko/library/caches/", new_file_name);
	tmp_fd = open(file_path, O_CREAT | O_WRONLY, 0644);
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
	int			i;

	i = 0;
	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)(finder->content);
			if (redirec->type == HEREDOC)
			{
				*is_heredoc = 1;
				new_tmp_file(redirec->file, i);
				redirec->type = HEREINPUT;
			}
			i++;
		}
		finder = finder->next;
	}
	return ;
}

void	delete_tmp_files(t_list *finder)
{
	t_redirect	*redirec;

	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)(finder->content);
			if (redirec->type == HEREINPUT)
				unlink(ft_strjoin("/Users/seongjko/library/caches/", \
				redirec->file));
		}
		finder = finder->next;
	}
	return ;
}

