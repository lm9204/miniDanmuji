/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:22:53 by yeondcho          #+#    #+#             */
/*   Updated: 2023/12/08 14:44:44 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *arg, ...)
{
	va_list	va_args;
	int		res;

	va_start(va_args, arg);
	res = read_format(arg, &va_args);
	va_end(va_args);
	if (res == -1)
		return (-1);
	return (res);
}

void	print_format(char c, va_list *va_arg, int *totallen)
{
	const char	*hex_lower = "0123456789abcdef";
	const char	*hex_upper = "0123456789ABCDEF";
	int			check;

	check = 0;
	if (c == 'd' || c == 'i')
		check = pr_num(va_arg);
	if (c == 'u')
		check = pr_uns(va_arg);
	if (c == 's')
		check = pr_str(va_arg);
	if (c == 'c')
		check = pr_char(va_arg);
	if (c == 'x')
		check = pr_hex(va_arg, hex_lower);
	if (c == 'X')
		check = pr_hex(va_arg, hex_upper);
	if (c == 'p')
		check = pr_addr(va_arg, hex_lower);
	if (c == '%')
		check = write(1, "%", 1);
	if (check == -1)
		*totallen = -1;
	if (*totallen != -1)
		*totallen += check;
}

int	read_format(const char *arg, va_list *va_arg)
{
	int		i;
	int		count;
	int		totallen;

	i = 0;
	count = 0;
	totallen = 0;
	while (arg[i] && totallen != -1)
	{
		if (arg[i] != '%')
			count++;
		else
		{
			print_normal(&arg[i - count], count, &totallen);
			if (totallen == -1)
				break ;
			if (arg[i] == '%' && i >= 1)
				count = 0;
			print_format(arg[++i], va_arg, &totallen);
		}
		i++;
	}
	if (i != 0 && count != 0 && totallen != -1)
		print_normal(&arg[i - count], count, &totallen);
	return (totallen);
}

void	print_normal(const char *arg, int len, int *totallen)
{
	int		write_len;

	write_len = write(1, arg, len);
	if (write_len == -1)
		*totallen = -1;
	if (*totallen != -1)
		*totallen += write_len;
}

int	pr_char(va_list *args)
{
	char	c;

	c = va_arg(*args, int);
	return (write(1, &c, 1));
}
