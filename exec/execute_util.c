/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:39:13 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/01 01:38:58 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many_cmds(t_list *finder)
{
	int		cmd_cnt;

	cmd_cnt = 0;
	while (finder && finder->flag != PIPE)
	{
		if (finder->flag == CMD)
			cmd_cnt++;
		finder = finder->next;
	}
	return (cmd_cnt);
}

int	how_many_pipes(t_list *finder)
{
	int	pipe_cnt;

	pipe_cnt = 0;
	while (finder)
	{
		if (finder->flag == PIPE)
			pipe_cnt++;
		finder = finder->next;
	}
	return (pipe_cnt);
}

t_list	*push_list_to_back(t_list *finder)
{
	while (finder)
	{
		if (finder->flag == PIPE)
		{
			finder = finder->next;
			break ;
		}
		finder = finder->next;
	}
	return (finder);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	is_unexecutable_file(char *path)
{
	struct stat	file_stat;

	if (access(path, F_OK) != 0)
		return (0);
	if (stat(path, &file_stat) < 0)
		return (-1);
	if (S_ISREG(file_stat.st_mode))
	{
		if (file_stat.st_mode & S_IXUSR)
			return (0);
		else
			return (1);
	}
	return (0);
}
