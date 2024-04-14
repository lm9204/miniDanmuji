/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:46 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/14 19:00:07 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data_struct(char **envp)
{
	t_data * data;
	
	data = (t_data *)malloc(sizeof(t_data));
	data->env_head = NULL;
	
	init_envp(&data->env_head, envp);
	data->splitted_exec_path = ft_split(ft_getenv("PATH", envp), ':');
	data->head = NULL;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt_msg = "minishell$ ";
	char		**res;
	char		*nl;
	t_data		*data;
	
	argc = 0;
	argv = 0;
	data = init_data_struct(envp);
	rl_clear_history();
	signal_handler(PARENT);
	nl = readline(prompt_msg);
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
		add_history(nl);
	}
}

//signal handling 관련

	// struct termios term;

    // //현재 터미널 속성 가져오기
    // if (tcgetattr(STDIN_FILENO, &term) != 0) {
    //     perror("tcgetattr");
    //     return 1;
    // }

	// rl_catch_signals = 0;

	//ECHOCTL 안 나타나도록 설정
	// term.c_lflag &= ~ECHOCTL;

	// //uncanonical mode로 설정
	// // term.c_lflag &= ~(ICANON | ECHO);
	// // term.c_cc[VMIN] = 1;
	// // term.c_cc[VTIME] = 0;

    // //변경된 터미널 속성 적용
    // if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0) {
    //     // perror("tcsetattr");
    //     return 1;
    // }
	// rl_catch_signals = 0;


	
	// if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
	// {
	// 	// perror("tcsetattr");
	// 	return 1;
	// }