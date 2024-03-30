/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_to_do.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:26:22 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/30 19:36:33 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cnt_node_until_pipe(t_list *finder)
{
    int cnt;

    cnt = 0;
    while (finder->flag != 1 && finder)
    {
        cnt++;
        finder = finder->next;
    }
    return (cnt);
}

int *categorize_cases(t_list *finder)
{
    int *flag_ary;
	int	i;

    flag_ary = (int *)malloc(sizeof(int) * cnt_node_until_pipe(finder));
	i = 0;
	while (finder->flag != 1 && finder)
	{
		finder->flag = flag_ary[i];
		finder = finder->next;
		i++;
	}
	return (flag_ary);
}


void	child_to_do(t_list *finder)
{
	int	*flag_ary;

	flag_ary = categorize_cases(finder);

	

}