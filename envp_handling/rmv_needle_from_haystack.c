/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmv_needle_from_haystack.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:03:38 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/29 15:54:33 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**rmv_needle_from_haystack(char **haystack, char *magnet)
{
	char	**res;
	int		column;
	int		h_i;
	int		r_i;

	column = cnt_column_line(haystack);
	res = (char **)malloc(sizeof(char *) * column);
	r_i = 0;
	h_i = 0;
	while (haystack[h_i])
	{
		if (!ft_strncmp(haystack[h_i], magnet, ft_strlen(magnet)))
		{
			free(haystack[h_i]);
			h_i++;
		}
		else
			res[r_i++] = haystack[h_i++];
	}
	*(res + column) = NULL;
	free(haystack);
	return (res);
}
