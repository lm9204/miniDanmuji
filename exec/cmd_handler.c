/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:07:07 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/03 14:17:02 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == name[j])
		{
			if (envp[i][j + 1] == '=')
				return (envp[i] + j + 2);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*joined_path(void *cmds, char **envp_path)
{
	char	*slash_path;
	t_cmd	*cmd_ary;
	char	*cmd_path;
	int		i;

	cmd_ary = (t_cmd *)cmds;
	i = -1;
	while (envp_path[++i])
	{
		slash_path = ft_strjoin(envp_path[i], "/");
		cmd_path = ft_strjoin(slash_path, cmd_ary->cmds[0]);
		if (!slash_path || !cmd_path)
		{
			perror("strjoin failed - joined_path\n");
			exit(1);
		}
		if (!access(cmd_path, X_OK))
		{
			free(slash_path);
			return (cmd_path);
		}
		free(slash_path);
		free(cmd_path);
	}
	return (0);
}

void	cmd_handler(t_list *finder, t_data *env)
{
	char	*cmd_path;
	t_cmd	*cmd_ary;

	cmd_ary = (t_cmd *)finder->content;
	while (finder && finder->flag != 1)
	{
		if (finder->flag == 0)
		{
			cmd_path = joined_path(finder->content, env->splitted_envp_path);
			execve(cmd_path, cmd_ary->cmds, env->envp);
			break ;
		}
	}
	return ;
}
