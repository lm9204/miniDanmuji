/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:04:22 by yeondcho          #+#    #+#             */
/*   Updated: 2023/12/22 20:34:50 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		strlen;
	int		strlen2;
	int		i;

	i = 0;
	strlen = ft_strlen(s1);
	strlen2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (strlen + strlen2 + 1));
	if (result == 0)
		return (0);
	while (i < strlen)
		result[i++] = *s1++;
	while (i < strlen + strlen2)
		result[i++] = *s2++;
	result[i] = 0;
	return (result);
}
