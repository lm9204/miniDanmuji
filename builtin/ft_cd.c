/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:46:11 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/26 15:17:28 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd(t_data *data)
{
	t_env	*old_pwd;
	t_env	*env_pwd;
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		tmp = data->pwd;
		free(tmp);
		data->pwd = ft_strdup(cwd);
		free(cwd);
	}
	env_pwd = find_env(&data->env_head, "PWD");
	old_pwd = find_env(&data->env_head, "OLDPWD");
	free(old_pwd->value);
	old_pwd->value = env_pwd->value;
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
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories:", 2);
	ft_putendl_fd(" No such file or directory", 2);
}

static int	ft_cd_error(char *path)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

int	ft_cd(t_data *data, char **path)
{
	char	*pwd;
	char	*home;

	if (!validate_arguments(path))
		return (1);
	home = find_env(&data->env_head, "HOME")->value;
	if (ft_strlen(path[0]) > 0)
	{
		chdir(path[0]);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			join_pwd(data, path[0]);
		else
			return (ft_cd_error(path[0]));
		free(pwd);
	}
	else if (home == NULL)
	{
		ft_putendl_fd("bash: cd: HOME not set", 2);
		return (1);
	}
	else
		chdir(home);
	update_pwd(data);
	return (0);
}
