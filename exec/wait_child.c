/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:02:25 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/16 20:57:33 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    wait_child(int child_cnt, t_data *data)
{
    int status;
    int exit_code;
    int i;

    i = 0;
    status = 0;
    while (i < child_cnt)
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            exit_code = WEXITSTATUS(status);
            data->exit_status = ft_itoa(exit_code);
        }
        i++;
    }   
}
