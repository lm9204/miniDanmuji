/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:46 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/26 17:47:23 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data_struct(char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->env_head = NULL;
	if (envp && *envp)
	{
		init_envp(&data->env_head, envp);
		data->splitted_exec_path = ft_split(ft_getenv("PATH", envp), ':');
		data->home = ft_strdup(find_env(&data->env_head, "HOME")->value);
		data->pwd = ft_strdup(find_env(&data->env_head, "PWD")->value);
	}
	else
	{
		data->splitted_exec_path = NULL;
		data->home = NULL;
		data->pwd = NULL;
	}
	data->head = NULL;
	data->exit_status = ft_strdup("0");
	data->expand_flag = 1;
	data->fork_flag = 0;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	const char		*prompt_msg = "minishell> \001\0337";
	char			**res;
	char			*nl;
	t_data			*data;

	extern int rl_catch_signals;
	argc = 0;
	argv = 0;
	rl_catch_signals = 0;
	data = init_data_struct(envp);
	rl_clear_history();
	signal_handler(PARENT);
	nl = readline(prompt_msg);
	sigterm_handler(nl, PARENT);
	add_history(nl);
	while (nl)
	{
		res = split_cmds(nl);
		parse_to_node(&data->head, res);
		// print_list(&data->head);
		if (data->head != NULL && validate_node_list(data))
			execute_main(&data->head, data);
		free(nl);
		free(res);
		clear_head(&data->head);
		nl = readline(prompt_msg);
		sigterm_handler(nl, PARENT);
		add_history(nl);
	}
	// system("leaks --list minishell");
}
