/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:51:21 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/02 15:15:20 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


int	main(int argc, char **argv, char **envp)
{
	const char	*prompt_msg = "minishell$ ";
	t_list	*head;
	// t_env	*env_head;
	t_data	*data;
	char	**res;
	char	*nl;
	int		i;

	argc = 0;
	argv = 0;
	data = malloc(sizeof(t_data));
	data->envp = init_envp(envp);
	head = NULL;
	nl = readline(prompt_msg);
	while (nl)
	{
		res = split_cmds(nl, data->envp);
		parse_to_node(&head, res);
		print_list(&head);
		free(nl);
		clear_head(&head);
		nl = readline(prompt_msg);
	}
	i = 0;
	// while (res[i])
	// 	printf("%s$\n", res[i++]);
}
