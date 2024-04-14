/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:13:35 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 17:31:47 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *append_newline(char *input)
{
    char *tmp;
    char *res;

    tmp = input;
    res = ft_strjoin(input, "\n");
    free(tmp);
    return (res);
}

char	*append_input(char *origin, char *input)
{
	char *res;
	char *tmp1;
	char *tmp2;

	tmp1 = origin;
	tmp2 = input;
	res = ft_strjoin(origin, input);
	free(tmp1);
	free(tmp2);
	return (res);
}

char    *get_input(t_redirect *redirec)
{
    char    *input;
    char    *res;

    res = (char *)malloc(sizeof(char));
	*res = '\0';
    input = readline("> ");
    input = append_newline(input);
    while (ft_strncmp(input, redirec->file, ft_strlen(redirec->file)) != 0)
    {
        res = append_input(res, input);
        input = readline("> ");
		input = append_newline(input);
    }
	free(input);
    return (res);
}

void    write_in_file(char *res, t_redirect *redirec)
{
    int tmp_fd;
    char *path;

    path = ft_strjoin("/Users/seongjko/library/caches/", redirec->new_file);
    printf("%s\n", path);
    tmp_fd = open(path, O_WRONLY, 0644);
    if (tmp_fd == -1)
    {
        printf("failed opening file2\n");
        exit(1);
    }
    write(tmp_fd, res, ft_strlen(res));
    close(tmp_fd);
    free(res);
    return ;
}

void	find_heredoc_and_get_input(t_list *finder)
{
	t_redirect	*redirec;
    char        *res;
	
	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)finder->content;
            if (redirec->type == HEREINPUT)
            {
                res = get_input(redirec);
                printf("%s\n", res);
                write_in_file(res, redirec);
            }
		}
		finder = finder->next;
	}
	return ;
}
