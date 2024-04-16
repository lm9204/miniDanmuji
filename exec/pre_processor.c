/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:15:57 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/16 20:58:52 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pre_processor(t_list *finder, t_data *data, t_process *process)
{
    heredoc_handler(finder);
    if (!how_many_cmds(finder))
		return (0);
    if (!how_many_pipes(finder) && is_it_builtin_pre((t_cmd *)finder->content))
    {
        builtin_handler((t_cmd *)finder->content, &env->env_head, process, env);
        return (0);
    }
    return (1);
}


