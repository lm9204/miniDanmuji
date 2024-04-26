/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:31:05 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/26 15:17:07 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env **head)
{
	t_env	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (ptr->value)
		{
			ft_putstr_fd(ptr->name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(ptr->value, 1);
		}
		ptr = ptr->next;
	}
	return (0);
}
