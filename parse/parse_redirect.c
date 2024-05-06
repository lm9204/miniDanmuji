/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:28:38 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/06 14:06:23 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redirect_arguments_error(char *cmd)
{
	ft_putstr_fd(PROMPT_MSG, 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
}

char	*parse_redir(t_data *data, char *cmd, int *redir_flag)
{
	char	*res;

	res = checkcmd(data, cmd, redir_flag);
	if (!res || res[0] == '\0')
		*redir_flag = 1;
	if (*redir_flag == 1)
		redirect_arguments_error(cmd);
	return (res);
}
