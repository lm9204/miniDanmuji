/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pre_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:41:03 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/12 20:52:34 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int signal_value;

void	get_heredoc_input(char *delimeter)
{
	char	*res;
	char	*res_tmp;
	char	*line;

	res = (char *)malloc(sizeof(char));
	*res = '\0';
	line = readline("> ");
	line = ft_strjoin(line, "\n");
	while (ft_strncmp(line, delimeter, ft_strlen(delimeter)))
	{
		res_tmp = ft_strjoin(res, line);
		free(res);
		free(line);
		res = res_tmp;
		line = readline("> ");
		line = ft_strjoin(line, "\n");
	}
	free(line);
	write_in_tmp_file(res, delimeter);
	return ;
}

void	check_heredoc(t_list *finder)
{
	t_redirect	*redirec;

	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)(finder->content);
			if (redirec->type == HEREINPUT)
				get_heredoc_input(redirec->file);
		}
		finder = finder->next;
	}
	return ;
}

void	heredoc_pre_handler(t_list *finder)
{
	int	is_heredoc;
	int	pid;
	int	status;
	
	is_heredoc = 0;
	status = 0;
	create_tmp_files(finder, &is_heredoc);
	if (!is_heredoc)
		return ;
	signal_value = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("failed fork\n");
		exit(1);
	}
	else if (pid == 0)
	{
		signal_handler_heredoc();
		check_heredoc(finder);
	}
	else
	{
		wait(&status);
		signal_value = 0;
	}
	return ;
}
