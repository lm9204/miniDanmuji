/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:19:11 by yeondcho          #+#    #+#             */
/*   Updated: 2023/10/10 18:27:45 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char		*needleptr;
	const char		*schptr;
	unsigned int	i;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		if (*haystack == *needle)
		{
			i = len - 1;
			needleptr = needle + 1;
			schptr = haystack + 1;
			while (i-- > 0 && *schptr != 0 && *needleptr == *schptr)
			{
				needleptr++;
				schptr++;
			}
			if (*needleptr == 0)
				return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (0);
}
