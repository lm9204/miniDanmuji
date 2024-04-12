/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:25:46 by seongjko          #+#    #+#             */
/*   Updated: 2024/04/12 15:20:35 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int signal_value = 0;

// int	main(int argc, char **argv, char **envp)
// {
// 	const char	*prompt_msg = "minishell$ ";
// 	t_list		*head;
// 	t_env		*env_head;
// 	char		**res;
// 	char		*nl;
// 	t_data		*data;

// 	struct termios term;

//     //현재 터미널 속성 가져오기
//     if (tcgetattr(STDIN_FILENO, &term) != 0) {
//         perror("tcgetattr");
//         return 1;
//     }

// 	//ECHOCTL 안 나타나도록 설정
// 	term.c_lflag &= ~ECHOCTL;

//     // 변경된 터미널 속성 적용
//     if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0) {
//         // perror("tcsetattr");
//         return 1;
//     }
// 	printf("hello world?\n");

// 	argc = 0;
// 	argv = 0;
// 	rl_catch_signals = 0;
// 	head = NULL;
// 	env_head = NULL;
// 	init_envp(&env_head, envp);
// 	rl_clear_history();
// 	signal_handler_parent();
// 	data = malloc(sizeof(t_data));
// 	data->envp = envp;
// 	data->splitted_envp_path = ft_split(ft_getenv("PATH", envp), ':');
// 	nl = readline(prompt_msg);
// 	add_history(nl);
// 	while (nl)
// 	{
// 		res = split_cmds(nl, &env_head);
// 		parse_to_node(&head, res);
// 		if (head != NULL && check_cmd(&head, data))
// 			execute_main(&head, data);
// 		free(nl);
// 		clear_head(&head);
// 		nl = readline(prompt_msg);
// 		add_history(nl);
		
// 	}
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
// 	{
// 		// perror("tcsetattr");
// 		return 1;
// 	}
// }
