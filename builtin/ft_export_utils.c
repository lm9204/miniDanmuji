/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:58:56 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/30 13:50:48 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sort_env_list(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	add_to_list(t_env **head, t_env *new)
{
	t_env	*ptr;

	ptr = *head;
	if (new == NULL)
		return ;
	if (ptr == NULL)
	{
		*head = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	export_list(char **env)
{
	int	i;
	int	j;

	i = 0;
	sort_env_list(env);
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		{
			ft_putchar_fd(env[i][j], 1);
			j++;
		}
		if (env[i][j] == '=')
		{
			ft_putchar_fd(env[i][j], 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(&env[i][j + 1], 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
	free_cmds(env);
}
