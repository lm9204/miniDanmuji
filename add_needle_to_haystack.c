/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_needle_to_haystack.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:59:03 by seongjko          #+#    #+#             */
/*   Updated: 2024/03/24 16:22:36 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal_sign(char *needle)
{
	int	i;

	i = 0;
	while (needle[i])
	{
		if (needle[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	front_or_back_of_equal_sign(char *needle)
{
	int	front;
	int	back;

	front = 0;
	back = 0;
	while (*needle != '=')
	{
		needle++;
		front++;
	}
	needle++;
	while (*needle)
	{
		needle++;
		back++;
	}
	if (front && back)
		return (1);
	return (0);
}

int	check_needle(char *needle)
{
	if (!is_equal_sign(needle))
		return (0);
	if (!front_or_back_of_equal_sign(needle))
		return (0);
	return (1);
}

char	**add_needle_to_haystack(char **haystack, char *needle)
{
	char	**res;
	int		column;
	int		i;

	if (!check_needle(needle))
		return (NULL);
	column = cnt_column_line(haystack);
	res = (char **)malloc(sizeof(char *) * (column + 1 + 1));
	i = -1;
	while (haystack[++i])
		res[i] = haystack[i];
	res[i] = needle;
	res[i + 1] = (char *)NULL;
	free(haystack);
	return (res);
}
