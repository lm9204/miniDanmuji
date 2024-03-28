/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:52:35 by yeondcho          #+#    #+#             */
/*   Updated: 2023/10/13 17:26:35 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	strlen;

	i = 0;
	strlen = ft_strlen(s);
	if (start >= strlen)
		len = 0;
	if (strlen < len)
		len = strlen;
	if (strlen - start < len)
		len = strlen - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (0);
	while (len-- > 0 && s[start])
	{
		ptr[i++] = s[start++];
	}
	ptr[i] = 0;
	return (ptr);
}
