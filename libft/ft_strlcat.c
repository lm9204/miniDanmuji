/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:45:46 by yeondcho          #+#    #+#             */
/*   Updated: 2023/10/06 17:37:17 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	srclen;
	unsigned int	dstlen;
	unsigned int	dstidx;
	unsigned int	srcidx;

	srclen = 0;
	dstlen = 0;
	while (src[srclen])
		srclen++;
	while (dst[dstlen] != 0)
		dstlen++;
	dstidx = dstlen;
	srcidx = 0;
	if (dstlen < dstsize)
	{
		while (src[srcidx] && srcidx < dstsize - dstlen - 1)
			dst[dstidx++] = src[srcidx++];
		dst[dstidx] = 0;
		return (dstlen + srclen);
	}
	else
		return (srclen + dstsize);
}
