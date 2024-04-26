/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:14:15 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/26 15:17:39 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char *data_pwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		ft_putendl_fd(pwd, 1);
	else
		ft_putendl_fd(data_pwd, 1);
	free(pwd);
	return (0);
}
