/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:51:21 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/12 15:20:23 by yeondcho         ###   ########.fr       */
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
		else
			i++;
		i++;
	}
	return (len);
}
void	print_env(t_env **head)
{
	t_env	*ptr;

	ptr = *head;
	while (ptr)
	{
		printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt_msg = "minishell$ ";
	t_list	*head;
	t_env	*env_head;
	char	**res;
	char	*nl;
	// int		i;

	argc = 0;
	argv = 0;
	printf("%d%p\n", argc, argv);
	head = NULL;
	env_head = NULL;
	init_envp(&env_head, envp);
	// print_env(&env_head);
	nl = readline(prompt_msg);
	while (nl)
	{
		res = split_cmds(nl, &env_head);
		parse_to_node(&head, res);
		print_list(&head);
		free(nl);
		free(res);
		clear_head(&head);
		nl = readline(prompt_msg);
	}
	free_env_list(&env_head);
	exit(0);
	// i = 0;
	// while (res[i])
	// 	printf("%s$\n", res[i++]);
}
