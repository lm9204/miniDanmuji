/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:37:13 by yeondcho          #+#    #+#             */
/*   Updated: 2023/10/13 16:27:10 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	checkof;
	void	*mem;

	mem = malloc(count * size);
	if (!count || !size)
		return (mem);
	if (mem == 0)
		return (0);
	checkof = count * size;
	if (size != 0 && checkof / count != size)
		return (0);
	ft_bzero(mem, count * size);
	return (mem);
}
