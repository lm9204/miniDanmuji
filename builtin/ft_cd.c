/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:46:11 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/16 20:43:27 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd(t_env **head, char *pwd)
{
	t_env	*tmp;
	char	*str;

	tmp = find_env(head, "PWD");
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = ft_strdup(pwd);
	}
	else
	{
		str = ft_strjoin("PWD=", pwd);
		addenv(head, str);
		free(str);
	}
}

static void	join_pwd(t_env **head, char *pwd, char *path)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(pwd, "/");
	res = ft_strjoin(tmp, path);
	free(tmp);
	tmp = pwd;
	pwd = res;
	free(tmp);
	update_pwd(head, pwd);
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
	int		ret;

	ret = 0;
	home = find_env(&data->env_head, "HOME")->value;
	if (ft_strlen(path) > 0)
	{
		ret = chdir(path);
		pwd = getcwd(NULL, 0);
		if (ret == -1 && !pwd)
			join_pwd(&data->env_head, data->pwd, path);
		else if (ret == -1 && pwd)
			ft_cd_error(path);
	}
	else if (home == NULL)
		ft_putendl_fd("bash: cd: HOME not set", 1);
	else
		ret = chdir(home);
	if (ret)
		update_pwd(&data->env_head, pwd);
}
