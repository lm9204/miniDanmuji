/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:01:32 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/02 16:55:01 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_envp(t_env **env_head, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		addenv(env_head, envp[i]);
		i++;
	}
}
