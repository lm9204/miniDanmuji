/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pre_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:41:03 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/03 16:56:31 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*tmp_file_handling(char *here_doc_input, char *delimeter, int i)
{
	int		tmp_fd;
	char	*file_index;
	char	*file_name;
	char	*file_path;

	file_index = ft_itoa(i);
	file_name = ft_strjoin(delimeter, file_index);
	file_path = ft_strjoin("/Users/seongjko/library/caches/", file_name);
	tmp_fd = open(file_path, O_CREAT | O_WRONLY, 0644);
	if (tmp_fd == -1)
	{
		printf("failed opening tmp file-heredoc\n");
		exit(1);
	}
	write(tmp_fd, here_doc_input, ft_strlen(here_doc_input));
	free(here_doc_input);
	free(file_index);
	free(file_path);
	close(tmp_fd);
	return (file_name);
}
char	*get_heredoc_input(char *delimeter, int i)
{
	char	*res;
	char	*res_tmp;
	char	*line;
	char	*ans;

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
	ans = tmp_file_handling(res, delimeter, i);
	return (ans);
}


void    heredoc_pre_handler(t_list *finder)
{
	t_redirect	*redirec;
	int			i;
	char		*new_file_name;

	i = 0;
	while (finder)
	{
		if (finder->flag == 2)
		{
			redirec = (t_redirect *)(finder->content);
			if (redirec->type == 0)
			{
				new_file_name = get_heredoc_input(redirec->file, i);
				redirec->type = 4;
				redirec->file = new_file_name;
				//나중에 new_file_name free 어떻게 할 거임?
				i++;
			}
		}
		finder = finder->next;
	}
}
