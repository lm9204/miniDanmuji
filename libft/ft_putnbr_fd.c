/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:27:30 by yeondcho          #+#    #+#             */
/*   Updated: 2023/11/30 16:17:33 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	result[11];
	int		i;

	i = 9;
	if (n < 0)
		write(fd, "-", 1);
	if (n == 0)
		write(fd, "0", 1);
	result[10] = 0;
	while (n != 0)
	{
		if (n < 0)
			result[i--] = n % 10 * -1 + 48;
		else
			result[i--] = n % 10 + 48;
		n /= 10;
	}
	write(fd, &result[i + 1], 9 - i);
}
