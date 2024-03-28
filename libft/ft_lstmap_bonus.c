/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:32:35 by yeondcho          #+#    #+#             */
/*   Updated: 2023/12/08 15:02:51 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*tmp;
	void	*val;

	nlst = 0;
	while (lst != 0)
	{
		tmp = (t_list *)ft_calloc(sizeof(t_list), 1);
		if (tmp == 0)
		{
			ft_lstclear(&nlst, del);
			return (0);
		}
		val = f(lst->content);
		tmp->content = val;
		ft_lstadd_back(&nlst, tmp);
		lst = lst->next;
	}
	return (nlst);
}
