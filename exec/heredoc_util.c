/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:49:41 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/02 14:25:13 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rmv_quotes(char *str) 
{
	int		len;
	char	*res;

	len = ft_strlen(str);
	res = (char *)malloc(len);
	strlcpy(res, str + 1, len);
    res[len - 2] = '\0';
	return (res);
}

int is_input_delimeter(char *input, char *delimeter, int expand_flag)
{
	char	*rmvd_quotes;
	int		flag;

	flag = 0;
	if (expand_flag == 1)
		return (ft_strncmp(input, delimeter, \
		ft_strlen(delimeter) + 1) != 10);
	else
	{
		rmvd_quotes = rmv_quotes(delimeter);
		if (ft_strncmp(input, rmvd_quotes, ft_strlen(rmvd_quotes) + 1) != 10)
			flag = 1;
		free(rmvd_quotes);
		return (flag);
	}
	return (0);
}