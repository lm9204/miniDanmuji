/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:49:41 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/03 21:59:11 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_input_delimeter(char *input, char *delimeter)
{
	return (ft_strncmp(input, delimeter, ft_strlen(delimeter) + 1) != 0);
}
