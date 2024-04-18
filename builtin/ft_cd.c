/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:46:11 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/18 14:45:29 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd(t_data *data)
{
	t_env	*env_pwd;
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		tmp = data->pwd;
		free(tmp);
		data->pwd = ft_strdup(cwd);
	}
	env_pwd = find_env(&data->env_head, "PWD");
	env_pwd->value = ft_strdup(data->pwd);
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
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 1);
	ft_putstr_fd("cannot access parent directories:", 1);
	ft_putendl_fd(" No such file or directory", 1);
}

static void	ft_cd_error(char *path)
{
	ft_putstr_fd("bash: cd: ", 1);
	ft_putstr_fd(path, 1);
	ft_putendl_fd(": No such file or directory", 1);
}

void	ft_cd(t_data *data, char *path)
{
	char	*pwd;
	char	*home;

	home = find_env(&data->env_head, "HOME")->value;
	if (ft_strlen(path) > 0)
	{
		chdir(path);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			join_pwd(data, path);
		else
			ft_cd_error(path);
	}
	else if (home == NULL)
		ft_putendl_fd("bash: cd: HOME not set", 1);
	else
		chdir(home);
	update_pwd(data);
}
