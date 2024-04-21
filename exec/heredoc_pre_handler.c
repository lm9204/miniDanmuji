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

char	*new_tmp_file(t_redirect *redirec, int i, t_data *env)
{
	char	*new_name;
	char	*path;
	char	*path_temp;
	int		tmp_fd;
	t_env	*home_direc;

	home_direc = find_env(&env->env_head, "HOME");
	//dangling 때문에 수정해야
	new_name = ft_strjoin(redirec->file, ft_itoa(i));
	path_temp = ft_strjoin(home_direc->value, "/library/caches/");
	path = ft_strjoin(path_temp, new_name);
	free(path_temp);
	redirec->new_file_path = path;
	tmp_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		printf("failed opening file1\n");
		exit(1);
	}
	close(tmp_fd);
	return (new_name);
}

void	convert_delimeter_to_file(t_list *finder, t_data *env)
{
	t_redirect	*redirec;
	int			i;

	i = 0;
	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)finder->content;
			if (redirec->type == 0)
			{
				redirec->new_file = new_tmp_file(redirec, i++, env);
				redirec->type = 4;
			}
		}
		finder = finder->next;
	}
	return ;
}

void	unlink_heredoc_files(t_list *finder)
{
	t_redirect	*redirec;

	while (finder)
	{
		if (finder->flag == REDIRECT)
		{
			redirec = (t_redirect *)finder->content;
			if (redirec->type == 4)
				unlink(redirec->new_file_path);
		}
		finder = finder->next;
	}
	return ;
}

void	heredoc_handler(t_list *finder, t_data *env)
{
	pid_t		pid;
	int			status;
	extern int	rl_catch_signals;

	convert_delimeter_to_file(finder, env);
	signal_handler(IGNORE);
	pid = fork();
	if (pid == 0)
	{
		signal_handler(HEREDOC);
		find_heredoc_and_get_input(finder);
		exit(0);
	}
	else
	{
		wait(&status);
		rl_catch_signals = 0;
		signal_handler(PARENT);
	}
	return ;
}
