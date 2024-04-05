/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:48:31 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/05 20:03:06 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_cmd(t_list **head, t_data *env)
{
    t_list	*finder;
	t_cmd	*cmd_ary;
    char	*cmd_path;

    finder = *head;
	cmd_ary = (t_cmd *)finder->content;
    while (finder)
    {
        if (finder->flag == 0)
        {
			cmd_path = joined_path(finder->content, env->splitted_envp_path);
			if (!cmd_path)
			{
				printf("Danmoujishell: %s: command not found\n", cmd_ary->cmds[0]);
				return (0);
			}
        }
        finder = finder->next;
    }
	return (1);
}