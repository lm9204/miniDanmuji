/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:18:07 by yeondcho          #+#    #+#             */
/*   Updated: 2023/12/08 15:02:29 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*ptr;
	int		i;

	i = 0;
	ptr = *lst;
	while (ptr != 0)
	{
		del(ptr->content);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	*lst = ptr;
	return (lst);
}
