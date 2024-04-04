/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:46 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/04 22:14:59 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt_msg = "minishell$ ";
	t_list		*head;
	t_env		*env_head;
	char		**res;
	char		*nl;
	t_data		*data;

	argc = 0;
	argv = 0;
	head = NULL;
	env_head = NULL;
	init_envp(&env_head, envp);
	signal_handler();
	data = malloc(sizeof(t_data));
	data->envp = envp;
	data->splitted_envp_path = ft_split(ft_getenv("PATH", envp), ':');
	nl = readline(prompt_msg);
	while (nl)
	{
		res = split_cmds(nl, &env_head);
		parse_to_node(&head, res);
		if (head != NULL)
        	execute_main(&head, data);
		// print_list(&head);
		free(nl);
		clear_head(&head);
		nl = readline(prompt_msg);
	}
}
