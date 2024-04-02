/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:46 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/02 17:36:01 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt_msg = "minishell$ ";
	t_list	*head;
	t_data	*data;
	char	**res;
	char	*nl;

	argc = 0;
	argv = 0;
	data = malloc(sizeof(t_data));
	data->envp = init_envp(envp);
	data->splitted_envp_path = ft_split(ft_getenv("PATH", envp), ':');
	head = NULL;
	nl = "hello";
	// nl = readline(prompt_msg);
	while (nl)
	{
		nl = readline(prompt_msg);
		res = split_cmds(nl, data->envp);
		parse_to_node(&head, res);
		// print_list(&head);
        execute_main(&head, data);
		printf("here?\n");
		free(nl);
		clear_head(&head);
	}
}


