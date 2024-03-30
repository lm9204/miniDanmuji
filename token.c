/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:51:21 by yeondcho          #+#    #+#             */
/*   Updated: 2024/03/30 22:20:22 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenlen(char **tokens)
{
	int	len;

	len = 0;
	while (tokens[len])
		len++;
	return (len);
}

int	token_cmds_len(char **tokens)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (tokens[i])
	{
		if (!is_symbol(tokens[i]))
			len++;
		i++;
	}
	return (len);
}


int	main(void)
{
	t_list	*head;
	char	*data;
	char	**res;
	int		i;

	head = NULL;
	data = readline("minishell $");
	res = split_cmds(data);
	i = 0;
	// while (res[i])
	// 	printf("%s$\n", res[i++]);
	parse_to_node(&head, res);
	print_list(&head);
}
