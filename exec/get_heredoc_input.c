/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:13:35 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/03 20:22:16 by seongjko         ###   ########.fr       */
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

char	*get_input(t_redirect *redirec, t_data *env, int expand_flag)
{
	char	*input;
	char	*res;

	res = (char *)malloc(sizeof(char));
	*res = '\0';
	input = readline("> ");
	sigterm_handler(input, HEREDOC);
	while (is_input_delimeter(input, redirec->file))
	{
		// printf("here?\n");
		if (input == NULL)
			return (res);
		if (expand_flag == 1)
			input = heredoc_newline(env, input);
		input = append_newline(input);
		res = append_input(res, input);
		input = readline("> ");
		sigterm_handler(input, HEREDOC);
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

int	check_expand_flag(char *delimeter)
{
	int i;
	int	quote;

	quote = 1;
	i = -1;
	while (delimeter[++i] && quote)
	{
		if (ft_isquotes(delimeter[i]) \
		&& findquotes(&delimeter[i + 1], delimeter[i]) != -1)
			quote = 0;
	}
	return (quote);
}

void	find_heredoc_and_save_input(t_list *finder, t_data *env)
{
	t_redirect	*redirec;
	char		*res;
	char		*tmp;
	int			expand_flag;
	extern int	rl_catch_signals;

	rl_catch_signals = 1;
	expand_flag = 0;
	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)finder->content;
			if (redirec->type == 4)
			{
				expand_flag = check_expand_flag(redirec->file);
				if (expand_flag == 0)
				{
					tmp = redirec->file;
					redirec->file = rmv_quotes(redirec->file);
					if (redirec->file != NULL)
						free(tmp);
					if (redirec->file == NULL)
						return ;
				}
				printf("delimeter: %s\n", redirec->file);
				printf("expand_flag: %d\n", expand_flag);
				res = get_input(redirec, env, expand_flag);
				write_in_file(res, redirec);
			}
		}
		finder = finder->next;
	}
	return ;
}
