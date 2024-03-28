/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:18:56 by yeondcho          #+#    #+#             */
/*   Updated: 2023/10/15 14:13:34 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr;
	const unsigned char	*srcptr;

	ptr = dst;
	srcptr = src;
	if (!src && !dst)
		return (0);
	if (dst <= src)
	{
		while (len-- > 0)
			*ptr++ = *srcptr++;
	}
	else
	{
		ptr += len - 1;
		srcptr += len - 1;
		while (len-- > 0)
			*ptr-- = *srcptr--;
	}
	return (dst);
}
