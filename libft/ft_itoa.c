/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:43:54 by yeondcho          #+#    #+#             */
/*   Updated: 2023/10/15 13:58:51 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getsize(int n);
static void	ft_strrev(char *str);

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	int		i;

	i = 0;
	size = getsize(n);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (result == 0)
		return (0);
	if (n < 0)
		result[i++] = '-';
	else if (n == 0)
		result[i++] = '0';
	while (n != 0)
	{
		if (n < 0)
			result[i++] = n % 10 * -1 + 48;
		else
			result[i++] = n % 10 + 48;
		n /= 10;
	}
	result[i] = 0;
	ft_strrev(result);
	return (result);
}

static void	ft_strrev(char *str)
{
	int	tmp;
	int	fr;
	int	ed;

	fr = 0;
	ed = ft_strlen(str) - 1;
	if (str[0] == '-')
		fr++;
	while (fr < ed)
	{
		tmp = str[fr];
		str[fr] = str[ed];
		str[ed] = tmp;
		fr++;
		ed--;
	}
}

static int	getsize(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}
