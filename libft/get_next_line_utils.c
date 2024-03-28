/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:01:48 by yeondcho          #+#    #+#             */
/*   Updated: 2023/12/08 15:11:24 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	delnode(t_gnl **lst, int fd)
{
	t_gnl	*node;
	t_gnl	*prev;

	node = *lst;
	prev = NULL;
	while (node)
	{
		if (node->fd == fd)
		{
			if (prev != NULL)
				prev->next = node->next;
			else
				*lst = node->next;
			free(node->buf);
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}

t_gnl	*lstaddnew(t_gnl **lst, int fd)
{
	t_gnl	*ptr;
	t_gnl	*new;

	ptr = *lst;
	new = malloc(sizeof(t_gnl));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->nl_idx = 0;
	new->next = NULL;
	new->buf = NULL;
	if (ptr == NULL)
	{
		*lst = new;
		return (*lst);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	return (new);
}

t_gnl	*lstschfd(t_gnl **lst, int fd)
{
	t_gnl	*ptr;

	ptr = *lst;
	if (fd == -1)
		return (NULL);
	while (ptr != 0)
	{
		if (ptr->fd == fd)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}
