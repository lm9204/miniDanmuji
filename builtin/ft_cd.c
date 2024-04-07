/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:46:11 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/06 20:27:23 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_env **head, char *path)
{
	t_env	*ptr;
	char	*home;

	ptr = find_env(head, "HOME", 0);
	home = ptr->value;
	if (ft_strlen(path) > 0)
		chdir(path);
	else
		chdir(home);
}
