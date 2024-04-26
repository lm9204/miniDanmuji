/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:24:31 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/26 13:48:14 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_arguments(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return (0);
	}
	return (1);
}
