/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:46:11 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/03 16:38:11 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd(t_data *data)
{
	t_env	*old_pwd;
	t_env	*env_pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		free(data->pwd);
		data->pwd = ft_strdup(cwd);
		free(cwd);
	}
	env_pwd = find_env(&data->env_head, "PWD");
	old_pwd = find_env(&data->env_head, "OLDPWD");
	if (env_pwd && old_pwd)
	{
		free(old_pwd->value);
		old_pwd->value = ft_strdup(env_pwd->value);
	}
	else if (old_pwd)
		old_pwd->value = ft_strdup(data->pwd);
	if (env_pwd)
	{
		free(env_pwd->value);
		env_pwd->value = ft_strdup(data->pwd);
	}
}

static void	join_pwd(t_data *data, char *path)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(data->pwd, "/");
	res = ft_strjoin(tmp, path);
	free(tmp);
	tmp = data->pwd;
	data->pwd = res;
	free(tmp);
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories:", 2);
	ft_putendl_fd(" No such file or directory", 2);
}

static int	ft_cd_error(char *path)
{
	ft_putstr_fd(PROMPT_MSG, 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

int	ft_cd(t_data *data, char **path)
{
	char	*pwd;
	char	*home;

	home = find_env(&data->env_head, "HOME")->value;
	if (ft_strlen(path[0]) > 0)
	{
		if (chdir(path[0]) == -1)
			return (ft_cd_error(path[0]));
		pwd = getcwd(NULL, 0);
		if (!pwd)
			join_pwd(data, path[0]);
		free(pwd);
	}
	else if (home == NULL)
	{
		ft_putstr_fd(PROMPT_MSG, 2);
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	else
		chdir(home);
	update_pwd(data);
	return (0);
}
