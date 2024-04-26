/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:51:00 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/26 15:15:07 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_newline(char *cmd, int *flag, int *newline)
{
	int	i;

	i = 1;
	if (cmd[0] != '-' || *flag)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] != 'n')
		{
			ft_putstr_fd(cmd, 1);
			*flag = 1;
			return (2);
		}
		i++;
	}
	*newline = 0;
	return (1);
}

int	ft_echo(char **cmds)
{
	int	newline;
	int	i;
	int	flag;

	i = 1;
	newline = 1;
	flag = 0;
	while (cmds[i])
	{
		if (!check_newline(cmds[i], &flag, &newline))
		{
			if (flag)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(cmds[i], 1);
			flag = 1;
		}
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
