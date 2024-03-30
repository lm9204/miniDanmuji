/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_needle_in_haystack.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:56:28 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/29 15:54:23 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_needle_pos(char *haystack)
{
	while (*haystack != '=')
		haystack++;
	return (haystack + 1);
}

char	*find_needle_in_haystack(char **haystack, char *magnet)
{
	char	*res;
	char	*temp;
	int		needle_len;

	while (*haystack)
	{
		temp = *haystack;
		if (!ft_strncmp(temp, magnet, ft_strlen(magnet)))
		{
			needle_len = ft_strlen(find_needle_pos(temp));
			res = (char *)malloc(sizeof(char) * (needle_len + 1));
			ft_strlcpy(res, find_needle_pos(temp), needle_len + 1);
			*(res + needle_len + 1) = (char)NULL;
			return (res);
		}
		haystack++;
	}
	return (NULL);
}
