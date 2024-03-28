/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:04:47 by yeondcho          #+#    #+#             */
/*   Updated: 2023/12/08 14:44:38 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pr_num(va_list *args)
{
	char	res[12];
	int		i;
	int		n;
	int		flag;

	flag = 0;
	n = va_arg(*args, int);
	i = 10;
	if (n < 0)
		flag = 1;
	if (n == 0)
		res[i--] = '0';
	while (n != 0)
	{
		if (n < 0)
			res[i--] = n % 10 * -1 + 48;
		else
			res[i--] = n % 10 + 48;
		n /= 10;
	}
	if (flag)
		res[i--] = '-';
	res[11] = 0;
	return (write(1, &res[i + 1], 10 - i));
}

int	pr_uns(va_list *args)
{
	char			res[12];
	unsigned int	n;
	unsigned int	i;

	i = 10;
	n = va_arg(*args, unsigned int);
	if (n == 0)
		res[i--] = '0';
	while (n != 0)
	{
		res[i--] = n % 10 + 48;
		n /= 10;
	}
	res[11] = 0;
	return (write(1, &res[i + 1], 10 - i));
}

//type 0 : char, 1 : string
int	pr_str(va_list *args)
{
	char	*s;
	int		len;

	s = va_arg(*args, char *);
	if (s == NULL)
		return (write(1, "(null)", 6));
	len = ft_strlen(s);
	return (write(1, s, len));
}

int	pr_hex(va_list *args, const char *hex)
{
	char			res[12];
	unsigned int	n;
	int				i;

	n = va_arg(*args, unsigned int);
	i = 10;
	if (n == 0)
		res[i--] = '0';
	while (n != 0)
	{
		res[i--] = hex[n % 16];
		n /= 16;
	}
	res[11] = 0;
	return (write(1, &res[i + 1], 10 - i));
}

int	pr_addr(va_list *args, const char *hex)
{
	char			res[19];
	unsigned long	n;
	int				i;

	i = 17;
	n = (unsigned long)va_arg(*args, void *);
	if (n == 0)
		res[i--] = '0';
	while (n != 0)
	{
		res[i--] = hex[n % 16];
		n /= 16;
	}
	res[i--] = 'x';
	res[i--] = '0';
	res[18] = 0;
	return (write(1, &res[i + 1], 17 - i));
}
