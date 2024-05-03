/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:44:26 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/03 22:14:17 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_expand_flag(char *delimeter)
{
	int	i;
	int	quote;

	quote = 1;
	i = -1;
	while (delimeter[++i] && quote)
	{
		if (ft_isquotes(delimeter[i]) \
		&& findquotes(&delimeter[i + 1], delimeter[i]) != -1)
			quote = 0;
	}
	return (quote);
}

int	control_quotes(int *expand_flag, t_redirect *redirec)
{
	char	*tmp;

	*expand_flag = check_expand_flag(redirec->file);
	if (*expand_flag == 0)
	{
		tmp = redirec->file;
		redirec->file = rmv_quotes(redirec->file);
		free(tmp);
		if (redirec->file == NULL)
			return (0);
	}
	return (1);
}
