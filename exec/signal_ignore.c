/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ignore.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:46:54 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 20:49:06 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    signal_ignore(void)
{
    signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
