/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:46 by seongjko          #+#    #+#             */
/*   Updated: 2024/05/06 14:59:15 by yeondcho         ###   ########.fr       */
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
	return (data);
}

t_data	*init_preset(int argc, char **argv, char **envp)
{
	extern int	rl_catch_signals;

	g_signal_flag = 0;
	rl_catch_signals = 0;
	argc = 0;
	argv = 0;
	rl_clear_history();
	signal_handler(PARENT);
	return (init_data_struct(envp));
}

void	global_signal(t_data *data)
{
	if (g_signal_flag == SIGINT)
	{
		free(data->exit_status);
		data->exit_status = ft_itoa(1);
		g_signal_flag = 0;
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	const char		*prompt_msg;
	char			**res;
	char			*nl;
	t_data			*data;

	prompt_msg = "minishell> \001\0337\002";
	data = init_preset(argc, argv, envp);
	while (1)
	{
		nl = readline(prompt_msg);
		global_signal(data);
		sigterm_handler(nl, PARENT);
		add_history(nl);
		res = split_cmds(nl);
		parse_to_node(&data->head, res);
		if (data->head != NULL && validate_node_list(data))
			execute_main(&data->head, data);
		free(nl);
		free(res);
		clear_head(&data->head);
		data->checkcmd_flag = 0;
	}
}
