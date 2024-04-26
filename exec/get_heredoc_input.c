/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:13:35 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/26 15:11:32 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_newline(char *input)
{
	char	*tmp;
	char	*res;

	tmp = input;
	res = ft_strjoin(input, "\n");
	free(tmp);
	return (res);
}

char	*append_input(char *origin, char *input)
{
	char	*res;
	char	*tmp1;
	char	*tmp2;

	tmp1 = origin;
	tmp2 = input;
	res = ft_strjoin(origin, input);
	free(tmp1);
	free(tmp2);
	return (res);
}

char	*get_input(t_redirect *redirec, t_data *env)
{
	char	*input;
	char	*res;

	(void)env;
	res = (char *)malloc(sizeof(char));
	*res = '\0';
	input = readline("> ");
	if (input == NULL)
		return (res);
	if (env->expand_flag == 1)
		input = checkcmd(env, input);
	input = append_newline(input);
	while (ft_strncmp(input, redirec->file, ft_strlen(redirec->file) + 1) != 10)
	{
		res = append_input(res, input);
		input = readline("> ");
		if (input == NULL)
			return (res);
		if (env->expand_flag == 1)
			input = checkcmd(env, input);
		input = append_newline(input);
	}
	free(input);
	return (res);
}

void	write_in_file(char *res, t_redirect *redirec)
{
	int	tmp_fd;

	tmp_fd = open(redirec->new_file_path, O_WRONLY, 0644);
	if (tmp_fd == -1)
	{
		printf("failed opening file\n");
		exit(1);
	}
	write(tmp_fd, res, ft_strlen(res));
	close(tmp_fd);
	free(res);
	return ;
}

void	find_heredoc_and_save_input(t_list *finder, t_data *env)
{
	t_redirect	*redirec;
	char		*res;
	extern int	rl_catch_signals;

	rl_catch_signals = 1;
	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)finder->content;
			if (redirec->type == 4)
			{
				res = get_input(redirec, env);
				write_in_file(res, redirec);
			}
		}
		finder = finder->next;
	}
	return ;
}
