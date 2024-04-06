/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:51:00 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/06 19:46:32 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *cmd, int newline)
{
	if (newline)
		ft_putendl_fd(cmd, 1);
	else
		ft_putstr_fd(cmd, 1);
}
