/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:46 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/15 03:09:43 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data_struct(char **envp)
{
	t_data *data;
	
	data = (t_data *)malloc(sizeof(t_data));
	data->env_head = NULL;
	
	init_envp(&data->env_head, envp);
	data->splitted_exec_path = ft_split(ft_getenv("PATH", envp), ':');
	data->head = NULL;
	return (data);
}

void	terminal_setting(struct termios *term)
{
	
    if (tcgetattr(STDIN_FILENO, term) != 0) {
        perror("tcgetattr");
        return ;
    }
    term->c_lflag &= ~ECHOCTL;
    if (tcsetattr(STDIN_FILENO, TCSANOW, term) != 0) {
        // perror("tcsetattr");
        return ;
    }
}

void	reset_terminal_setting(struct termios *term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) != 0)
	{
		perror("tcsetattr");
		return ;
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt_msg = "\033[32mMinishell>\033[0m ";
	char		**res;
	char		*nl;
	t_data		*data;
	struct		termios term;
	
	
	argc = 0;
	argv = 0;
	terminal_setting(&term);
	data = init_data_struct(envp);
	rl_clear_history();
	signal_handler(PARENT);
	nl = readline(prompt_msg);
	sigterm_handler(nl, PARENT);
	add_history(nl);
	while (nl)
	{
		res = split_cmds(nl, &data->env_head);
		parse_to_node(&data->head, res);
		if (data->head != NULL && check_cmd(&data->head, data))
			execute_main(&data->head, data);
		free(nl);
		clear_head(&data->head);
		nl = readline(prompt_msg);
		sigterm_handler(nl, PARENT);
		add_history(nl);
	}
	reset_terminal_setting(&term);
}
