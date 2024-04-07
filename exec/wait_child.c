/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:02:25 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/07 17:05:13 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    wait_child(int child_cnt)
{
    int status;
    int i;

    i = 0;
    status = 0;
    while (i < child_cnt)
    {
        wait(&status);
        kill(0, SIGINT);
        //자식 프로세스의 종료 상태 확인하는 코드
        i++;
    }

    
}
