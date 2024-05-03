/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:28:01 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/03 16:35:12 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' \
	|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static void	ft_exit_error(char *input)
{
	ft_putstr_fd(PROMPT_MSG, 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(input, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(255);
}

static long long	ft_atoi_ovf(char *str)
{
	long long	prev;
	long long	res;
	long long	sign;
	int			i;

	sign = 1;
	res = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			ft_exit_error(str);
		prev = res;
		res *= 10;
		res += (str[i] - 48) * sign;
		if ((res % 10) != (str[i] - 48) * sign || (res / 10 != prev))
			ft_exit_error(str);
		i++;
	}
	return (res);
}

int	ft_exit(char **input)
{
	long long	number;

	number = 0;
	if (!validate_arguments(input))
		return (1);
	if (ft_strlen(input[0]) > 0)
		number = ft_atoi_ovf(input[0]);
	ft_putendl_fd("exit", 1);
	exit(number % 256);
}
