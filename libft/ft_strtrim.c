/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:03:19 by yeondcho          #+#    #+#             */
/*   Updated: 2023/10/13 17:43:31 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		isset(char c, char const *set);
void	geteachsetlen(char const *s1, char const *set, int *fr, int *ed);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		front;
	int		end;
	int		strlen;
	int		i;

	if (!s1 || !s1[0] || !set)
		return (ft_calloc(1, 1));
	i = 0;
	strlen = ft_strlen(s1);
	front = 0;
	end = strlen - 1;
	if (end < 0)
		end = 0;
	geteachsetlen(s1, set, &front, &end);
	strlen -= (strlen - end) + (front - 2);
	result = (char *)malloc(sizeof(char) * (strlen));
	if (result == 0)
		return (0);
	while (front <= end)
		result[i++] = s1[front++];
	result[i] = 0;
	return (result);
}

void	geteachsetlen(char const *s1, char const *set, int *fr, int *ed)
{
	int	i;

	i = *ed / 2;
	while (s1[*fr] && isset(s1[*fr], set) && *fr <= i)
		(*fr)++;
	while (s1[*ed] && isset(s1[*ed], set) && *ed >= i)
		(*ed)--;
}

int	isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
