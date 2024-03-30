/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:51:21 by yeondcho          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/30 20:29:17 by yeondcho         ###   ########.fr       */
=======
/*   Updated: 2024/03/29 15:53:17 by seongjko         ###   ########.fr       */
>>>>>>> 531ff459c567ff851e34a4be42c1898496c89492
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


<<<<<<< HEAD
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
=======
// int	main(void)
// {
// 	t_list	*head;
// 	char	*data;
// 	char	**res;
// 	int		i;

// 	head = NULL;
// 	data = readline("minishell $");
// 	res = split_cmds(data);
// 	i = 0;
// 	parse_to_node(&head, res);
// 	print_list(&head);
	 
// }
>>>>>>> 531ff459c567ff851e34a4be42c1898496c89492
