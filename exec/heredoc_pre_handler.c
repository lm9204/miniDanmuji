/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:41:03 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 20:53:15 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*new_tmp_file(t_redirect *redirec, int i)
{
	char	*new_name;
	char	*path;
	int		tmp_fd;

	new_name = ft_strjoin(redirec->file, ft_itoa(i));
	path = ft_strjoin("/Users/seongjko/library/caches/", new_name);
	printf("%s\n", path);
	tmp_fd = open(path, O_CREAT | O_WRONLY, 0644);
	if (tmp_fd == -1)
	{
		printf("failed opening file1\n");
		exit(1);
	}
	close(tmp_fd);
	return (new_name);
}

void	convert_delimeter_to_file(t_list *finder)
{
	t_redirect *redirec;
	int	i;
	
	i = 0;
	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)finder->content;
			if (redirec->type == 0)
			{
				redirec->new_file = new_tmp_file(redirec, i++);
				printf("%s\n", redirec->new_file);
				redirec->type = 4;
			}
		}
		finder = finder->next;
	}
	return ;
}

void	heredoc_handler(t_list *finder)
{
	pid_t	pid;
	int	status;

	convert_delimeter_to_file(finder);
	signal_handler(IGNORE);
	pid = fork();
	if (pid == 0)
	{
		signal_handler(HEREDOC);
		find_heredoc_and_get_input(finder);
		exit(1);
	}
	else
	{
		wait(&status);
		signal_handler(PARENT);
	}
	return ;
}
