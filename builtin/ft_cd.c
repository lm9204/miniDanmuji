/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:46:11 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/15 19:26:59 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_env **head, char *path)
{
	t_env	*ptr;
	char	*pwd;
	char	*home;
	// char	*tmp;

	pwd = getcwd(NULL, 0);
	ptr = find_env(head, "HOME");
	home = ptr->value;
	if (ft_strlen(path) > 0)
	{
		printf("%s\n", path);
		chdir(path);
		printf("%s\n", getcwd(NULL, 0));
	}
	else if (home == NULL)
		ft_putendl_fd("bash: cd: Home not set", 1);
	else
		chdir(home);
}
